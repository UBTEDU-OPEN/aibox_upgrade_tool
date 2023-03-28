#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <QBitmap>
#include <QPainter>
#include <QMouseEvent>
#include <QFileDialog>
#include <thread>
#include <QProcess>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <unistd.h>
#include "ciniconfig.h"
#include "ota_close_guide.h"
//#include "dialogtips.h"

#include <QLoggingCategory>
#include <QMovie>

Q_LOGGING_CATEGORY(upgrade_tool, "upgrade_tool")


const static QString kSavePath = "/opt/ota_package/ubtech";
const static QString kKeyFilePath = "/tmp/ota_key";
const static int kKeyValue = 456701;

Mainwindow::Mainwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mainwindow)
  , m_bIsImport(false)
  , m_strFilePath("")
  , m_bIsCloseTipsState(false)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint); 
    this->setStyleSheet("Mainwindow{background-color:#9EB2C0;}");
    //屏幕居中
    this->setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,this->size(),qApp->desktop()->availableGeometry()));
    //圆角
    QBitmap bmp(this->size());
    bmp.fill();
    QPainter painter(&bmp);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawRoundedRect(bmp.rect(), 10, 10);
    setMask(bmp);
    m_titlebar = new titlebar();
//    m_content = new content();
    m_dialog = new dialog();
    m_mask = new tempmask();
    m_pCloseTips = new OtaCloseGuide();
    connect(m_pCloseTips, &OtaCloseGuide::sigClose, this, &Mainwindow::onTipsClose);
    ui->horizontalLayout_2->addWidget(m_titlebar);
//    ui->verticalLayout->addWidget(m_content);

    connect(m_titlebar, &titlebar::SigMin, this, &Mainwindow::showMinimized);
    connect(m_titlebar, &titlebar::SigClose, this, &Mainwindow::onShowCloseTips);
//    connect(m_content, &content::sigStart, this, &Mainwindow::showDialog);
    connect(m_dialog, &dialog::showMask, m_mask, &tempmask::showMask);
    connect(m_mask, &tempmask::sigShowWinMsg, this, &Mainwindow::onShowWinMsg);
    connect(m_mask, &tempmask::sigUpgradeFail, this, &Mainwindow::onUpgradeFail);
    ui->stackedWidget->setCurrentIndex(ePagesIndexEntrance);
    initOtaWindowsMsg();
    m_pMovie = new QMovie(QString(":/icon/loading.gif"));
    ui->pBNext->setEnabled(false);
}

Mainwindow::~Mainwindow()
{
    SAFE_DELETE(m_pMovie);
    delete ui;
}

QString Mainwindow::getCurVersion()
{
    std::string strVersion= read("/etc/aibox_sw_version");
//    qCDebug(upgrade_tool())() << "GetVersion version:" << strVersion.c_str();
    QString strRawVersion = QString::fromStdString(strVersion);
    QString strpuleVersion = strRawVersion.left(strRawVersion.indexOf('\n'));
    strpuleVersion.replace("AIbox_", "");
    return strpuleVersion;
}

std::string Mainwindow::read(const std::string &filePath)
{
    std::string strContent = "";
    FILE* fp = fopen(filePath.c_str(), "rb");
    if(!fp)
    {
       return "";
    }
    char data[LITTLE_FILE_CONTENT_LEN + 1] = {0};
    fread((void*)data, LITTLE_FILE_CONTENT_LEN, 1, fp);
    strContent = data;
    //    std::string str((std::istreambuf_iterator<char>(t)),
    //                     std::istreambuf_iterator<char>());
    SAFE_FCLOSE(fp);
    return strContent;
}

void Mainwindow::showDialog()
{
    m_dialog->setParent(this);
    m_dialog->showStep1();
}

void Mainwindow::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        m_ptPre = e->globalPos();
        m_bLeftDown = true;
    }
    else
    {
        m_bLeftDown = false;
    }
    return QWidget::mousePressEvent(e);
}

void Mainwindow::mouseMoveEvent(QMouseEvent *e)
{
    if(!(windowState() & Qt::WindowMaximized))
    {
        if(m_bLeftDown && m_titlebar->rect().contains(mapFromGlobal(m_ptPre))) //暂时不支持拉伸
        {
            QPoint nowPt = e->globalPos();
            QPoint moveTo = mapToParent(nowPt - m_ptPre);
            move(moveTo);
            m_ptPre = nowPt;
        }
    }
    QWidget::mouseMoveEvent(e);
}

void Mainwindow::mouseReleaseEvent(QMouseEvent *e)
{

    m_bLeftDown = false;
    QWidget::mouseReleaseEvent(e);
}

void Mainwindow::on_pbUpgrade_clicked()
{
    showDialog();
}

void Mainwindow::on_pBNext_clicked()
{
    ui->stackedWidget->setCurrentIndex(ePagesIndexImporting);
    ui->pBEnterUpdatePage->hide();
    ui->lb_checkPack->setText(tr("正在校验升级包，大概需要5-10分钟时间，请耐心等待......"));
    ui->labelGif->setMovie(m_pMovie);
    m_pMovie->start();
    std::thread ([this]()
    {
        bool bIsDelta = false;
        int  nState = eStateWaiting;
        QString strOtaFilePath = "";
        do
        {
            QString strFilePath =  m_strFilePath;
            qCDebug(upgrade_tool()) << "importWidget::onNextClicked strFilePath = " << strFilePath;
            if (!QFile::exists(strFilePath))
            {
                nState = eStateImportFailedFileOpenFail;
                qCDebug(upgrade_tool()) << "importWidget::onNextClicked strFilePath is not exist\n";
                break;
            }
#if 1
            //删除旧文件
            system("rm -rf /opt/ota_package/ubtech/*.tar.gz /opt/ota_package/ubtech*.ini");
            //解压
            QString strUnTarCmd = "tar -xf " + m_strFilePath + " -C " + kSavePath;
            qCDebug(upgrade_tool()) << "importWidget::onNextClicked strUnTarCmd =" << strFilePath;
            system(strUnTarCmd.toStdString().data());

#endif

            //解压后获取版本和md5
            QString strConfigFilePath  = kSavePath + QDir::separator() + OTA_CONFIG_FILE_NAME;
            if (!QFile::exists(strConfigFilePath))
            {
                nState = eStateImportFailedFileOpenFail;
                qCDebug(upgrade_tool()) <<  "on_pBNext_clicked::onNextClicked strFilePath uRar ota config file failed\n";
                break;
            }

            qCDebug(upgrade_tool()) <<"on_pBNext_clicked::onNextClicked strConfigFilePath =" << strConfigFilePath;
            QString strAllMd5Key = CIniConfig::getKey(OTA_CONFIG_KEY,
                                                   OTA_CONFIG_ALL_MD5_KEY);
            QString strAllMd5;
            CIniConfig::getValue(strConfigFilePath, strAllMd5Key, strAllMd5);
            QString strDeltaMd5;
            qCDebug(upgrade_tool()) << "on_pBNext_clicked::onNextClicked strAllMd5 = "<< strAllMd5;
            if (!strAllMd5.isEmpty())//包是ok的
            {
                QString strDeltaMd5Key = CIniConfig::getKey(OTA_CONFIG_KEY,
                                                       OTA_CONFIG_DELTA_MD5_KEY);

                CIniConfig::getValue(strConfigFilePath, strDeltaMd5Key, strDeltaMd5);

                qCDebug(upgrade_tool()) << "on_pBNext_clicked::onNextClicked strAllMd5 = "<< strConfigFilePath;
                if (strDeltaMd5.isEmpty())
                {
                    //全量
                    QString strToVersionKey= CIniConfig::getKey(OTA_CONFIG_KEY,
                                                              OTA_CONFIG_TO_VERSION_KEY);
                    QString strToVersion;
                    CIniConfig::getValue(strConfigFilePath, strToVersionKey, strToVersion);

                    QString strCurVersion = getCurVersion();
                    qCDebug(upgrade_tool()) << "on_pBNext_clicked::onNextClicked strToVersion  " << strToVersion << " strCurVersion = " << strCurVersion;
                    if (CompareVersion(strCurVersion, strToVersion) != -1) //当前版本比升级的版本低或相等
                    {
                        nState = eStateImportFailedOther;
                        break;
                    }
                }
                else
                {
                    QString strFromVersionKey= CIniConfig::getKey(OTA_CONFIG_KEY,
                                                              OTA_CONFIG_FROM_VERSION_KEY);
                    QString strFromVersion;
                    CIniConfig::getValue(strConfigFilePath, strFromVersionKey, strFromVersion);

                    QString strCurVersion = getCurVersion();
                    qCDebug(upgrade_tool()) << "on_pBNext_clicked::onNextClicked strFromVersion =  " << strFromVersion << " strCurVersion =" << strCurVersion;
                    if (CompareVersion(strFromVersion, strCurVersion) != 0)
                    {
                        nState = eStateImportFailedOther;
                        break;
                    }
                    bIsDelta = true;
                }
            }
            else
            {
                nState = eStateImportFailedOther;
                break;
            }

            strOtaFilePath = kSavePath + QDir::separator() + strAllMd5 + UBT_TAR_GZ_FILE_EXT;
            if (!QFile::exists(strOtaFilePath))
            {
                nState = eStateImportFailedFileOpenFail;
                qCDebug(upgrade_tool()) << "on_pBNext_clicked::onNextClicked strFilePath uRar ota file failed\n";
                break;
            }
            qCDebug(upgrade_tool()) << "on_pBNext_clicked::onNextClicked strOtaFilePath = " << strOtaFilePath;


            QString cmd = "md5sum " + strOtaFilePath;

            FILE *fp = popen(cmd.toStdString().data(), "r");
            if (fp)
            {
                char md5sumBuf[128] = {0};
                fread(md5sumBuf, 1, sizeof(md5sumBuf), fp);
                pclose(fp);
                QString strMd5New = QString(md5sumBuf);
                int pos = strMd5New.indexOf(" ");
                strMd5New = strMd5New.mid(0, pos);
                QString strMd5 = strAllMd5;
                if (bIsDelta)
                {
                    strMd5 = strDeltaMd5;
                    QString strTime = ui->label_tips_time->text();
                    strTime.replace("45", "120");
                    ui->label_tips_time->setText(strTime);

                }
                qCDebug(upgrade_tool()) << "on_pBNext_clicked::onNextClicked strMd5New = " <<  strMd5New << "strMd5 = " <<  strMd5;
                if (strMd5.compare(strMd5New, Qt::CaseInsensitive) == 0)
                {
                    nState = eStateImportSuccess;
                    ui->lb_checkPack->setText(tr("当前升级包可用于本设备升级"));
                    ui->pBEnterUpdatePage->show();
                    ui->pBEnterUpdatePage->setText(tr("下一步"));
                    ui->labelGif->setPixmap(QPixmap(":/icon/img_remove_success.png"));
                    m_bIsImport = true;

                    if (m_mask)
                    {
                        m_mask->SetOtaFile(bIsDelta, strAllMd5 + UBT_TAR_GZ_FILE_EXT);
                    }
                }
                else
                {
                    nState = eStateImportFailedMd5;
                }
            }
        }while(0);

        if (nState != eStateImportSuccess)
        {
            nState = eStateImportFailedMd5;
            ui->lb_checkPack->setText(tr("当前升级包不可用，请重新下载"));
            ui->pBEnterUpdatePage->show();
            ui->labelGif->setPixmap(QPixmap(":/icon/img_remove_fail.png"));
            ui->pBEnterUpdatePage->setText(tr("返回"));
        }

    }).detach();
}

void Mainwindow::on_pBEnterUpdatePage_clicked()
{
    if (m_bIsImport)
    {
        ui->stackedWidget->setCurrentIndex(ePagesIndexUpgrade);
        ui->pBEnterUpdatePage->hide();
    }
    else
    {
        ui->stackedWidget->setCurrentIndex(ePagesIndexImport);
    }

}

void Mainwindow::on_pbEnter_clicked()
{
    ui->stackedWidget->setCurrentIndex(ePagesIndexImport);
}

void Mainwindow::on_pBImport_clicked()
{
    QString sFmtTitle = tr("tar File");
    QString sFmt;
    sFmt.sprintf("%s(*%s)", sFmtTitle.toStdString().c_str(), UBT_TAR_FILE_EXT);
    //      QString sAppLocalDownLoadPath = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
    QString strFilePathName = QFileDialog::getOpenFileName(NULL, tr("Open file"), /*"/home/oneai/Downloads"*/QString(), sFmt); //选择路径
    if(strFilePathName.isEmpty())
    {
        //CMessageBox::warning(this, "", "打开文件路径为空");
        qCDebug(upgrade_tool()) << "MainWindow::Import strFileName Empty return\n";
        return;
    }
    m_strFilePath = strFilePathName;
    qCDebug(upgrade_tool()) << "Import strFileName = ", strFilePathName;
    strFilePathName = QDir::toNativeSeparators(strFilePathName);

//    if(!CheckFile(strFilePathName))
//    {
//        qCDebug(upgrade_tool())("MainWindow::Import CheckFile fail return\n");
//        return;
//    }
    QFileInfo filePath(strFilePathName);
    QString strFileName = filePath.fileName();
    ui->lEOtaPath->setText(strFileName);
    ui->pBNext->setEnabled(true);
}

int Mainwindow::CompareVersion(QString strVersion1, QString strVersion2)
{
    if (!strVersion1.compare(strVersion2))
    {
        return 0;
    }

    QStringList list1 = strVersion1.split( "." );
    QStringList list2 = strVersion2.split( "." );

    int iTotal1 = list1.count();
    int iTotal2 = list2.count();

    int iTotal=iTotal1>iTotal2?iTotal2:iTotal1;

    int iValue1 = 0, iValue2 = 0;
    bool ibOK1 = false, ibOK2 = false;
    for ( int iNum = 0; iNum < iTotal; ++iNum )
    {
        iValue1 = list1[iNum].toInt( &ibOK1 );
        if (!ibOK1)
        {
            iValue1=0;
        }

        iValue2 = list2[iNum].toInt( &ibOK2 );
        if (!ibOK2)
        {
            iValue2=0;
        }

        if (iValue1==iValue2)
        {
            continue;
        }
        else if ( iValue1 < iValue2 )
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }
    return iTotal1<iTotal2?-1:1;
}


bool Mainwindow::initOtaWindowsMsg()
{
    qCDebug(upgrade_tool()) << "enter " << __func__;
    QFile keyFile(kKeyFilePath);

    if (!keyFile.exists())
    {
        if (!keyFile.open(QIODevice::ReadWrite))
        {
            qCCritical(upgrade_tool()) << "open " << kKeyFilePath << " fail";
            return false;
        }
        else
        {
            keyFile.close();
        }
    }

    QString cmd = "chmod 0666 " + kKeyFilePath;
    system(cmd.toStdString().data());

    key_t key = ftok(kKeyFilePath.toStdString().data(), 6);
    qCDebug(upgrade_tool()) << "ftok key: " << key;
    if (key < 0)
    {
        key = (key_t)kKeyValue;
    }

    m_nMsgId = msgget(key, IPC_CREAT | 0666);
    qCDebug(upgrade_tool()) << "msgget result, m_nMsgId is: " << m_nMsgId;
    if (m_nMsgId < 0)
    {
        qCDebug(upgrade_tool()) << "msgget error " << m_nMsgId;
        return false;
    }

    return true;
}

void Mainwindow::sendOtaWindowsMsg(emResultState eState)
{
    qCDebug(upgrade_tool()) << "enter " << __func__;
    OtaMessage msg;
    msg.eState = eState;
    msg.type = 1;

    int re = msgsnd(m_nMsgId, &msg,  sizeof(msg) - sizeof(msg.type), 0);
    qCDebug(upgrade_tool()) << "msgsnd result " << re << ", msg state " << eState;
}

void Mainwindow::onShowWinMsg(emResultState eState)
{
    sendOtaWindowsMsg(eState);
}

void Mainwindow::onUpgradeFail()
{
    m_dialog->hide();
    ui->stackedWidget->setCurrentIndex(ePagesIndexImport);
}

void Mainwindow::onShowCloseTips()
{
    if (m_bIsCloseTipsState)
    {
        return;
    }
    m_bIsCloseTipsState = true;
    m_pCloseTips->setParent(this);
    m_pCloseTips->show();
}

void Mainwindow::onTipsClose(bool bState)
{
    if (bState)
    {
        close();
    }
    m_bIsCloseTipsState = false;
    m_pCloseTips->hide();
}
