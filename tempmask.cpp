#include "tempmask.h"
#include "ui_tempmask.h"
#include <QThread>
#include <QTimer>
#include <QDesktopWidget>
#include "ciniconfig.h"
#include "setting.h"


tempmask::tempmask(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tempmask)
  , m_bDelt(false)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint| Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint | Qt::ToolTip);
    this->setWindowOpacity(1);
    setAttribute(Qt::WA_TranslucentBackground, true);
//    setAttribute(Qt::WA_StyledBackground);

    this->setFixedSize(QApplication::desktop()->screenGeometry().width(),QApplication::desktop()->screenGeometry().height());
    ui->widget_2->setStyleSheet("background-color:rgba(0,0,0,30)");
    ui->widget_3->setStyleSheet("background:#FFFFFF;border-radius:10px");
    ui->lbsecs->setStyleSheet("font-size: 100px;color: #FC2864;");
    ui->label->setStyleSheet("font-size: 14px;color: #4C545B;line-height: 24px;");
    ui->label_2->setStyleSheet("font-size: 14px;color: #4C545B;line-height: 24px;");

    m_showTimer = new QTimer();
    connect(m_showTimer, &QTimer::timeout, this, &tempmask::doUpgrade);
    m_showTimer->setSingleShot(false);
    seconds = 2;

    hide();
}

tempmask::~tempmask()
{
    delete ui;
}

void tempmask::SetOtaFile(bool  bDelt, QString strOtaFile)
{
    m_bDelt = bDelt;
    m_strOtaFile = strOtaFile;
}

void tempmask::showMask()
{
    if (m_bDelt)
    {
        setOtaResultState('3');//预先设置为失败，这样合包中断也会提示失败
        emit sigShowWinMsg(Updating);
        QString cmdPath = "/opt/ota_package/ubtech/recovery.sh";
        QString update =  cmdPath + " update " + m_strOtaFile;
        int nRet = system(update.toStdString().data());
        emit sigShowWinMsg(UpdateImageError);
        setOtaResultState('0');//恢复状态
        QTimer::singleShot(500, this, SLOT(UpgradeFail()));

    }
    else
    {
        show();
        m_showTimer->start(1000);
    }

}

void tempmask::setOtaResultState(char state)
{
    QString cmd = "echo " + QString(state) + " > " + "/opt/ota_package/ubtech/state";
    system(cmd.toStdString().data());
}


void tempmask::doUpgrade()
{
    if(seconds > 0)
    {
        ui->lbsecs->setText(QString::number(seconds));
        seconds--;
        m_showTimer->start(1000);
    }
    else if(seconds == 0)
    {
        m_showTimer->stop();
        hide();
        QString cmdPath = "/opt/ota_package/ubtech/recovery.sh";
        QString update =  cmdPath + " update " + m_strOtaFile;
        int nRet = system(update.toStdString().data());
    }
}

void tempmask::countdown()
{

}

void tempmask::UpgradeFail()
{
    emit sigUpgradeFail();
}
