#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "titlebar.h"
#include "ui_titlebar.h"
#include "dialog.h"
#include "ui_dialog.h"
#include "tempmask.h"
#include "ui_tempmask.h"
#include "ota_close_guide.h"

namespace Ui {
class Mainwindow;
}

enum emImportState
{
    eStateWaiting = 1,
    eStateImportSuccess,
    eStateImportFailedMd5,
    eStateImportFailedFileOpenFail,
    eStateImportFailedOther,
};

enum emOtaPageIndex
{
    ePagesIndexEntrance = 0,
    ePagesIndexImport,
    ePagesIndexImporting,
    ePagesIndexUpgrade,
};

const QString OTA_CONFIG_FILE_NAME = "config.ini";
const QString OTA_CONFIG_KEY = "Config";
const QString OTA_CONFIG_ALL_MD5_KEY = "AllMd5";
const QString OTA_CONFIG_DELTA_MD5_KEY = "DeltaMd5";
const QString OTA_CONFIG_FROM_VERSION_KEY = "From_version";
const QString OTA_CONFIG_TO_VERSION_KEY = "To_version";

#define LITTLE_FILE_CONTENT_LEN 128 //小文件内容长度限制128(版本号,状态之类的文件)
#define SAFE_FCLOSE(p)         if(p){ fclose(p); p = NULL;}

#define     UBT_TAR_FILE_EXT            ".tar"
#define     UBT_RAR_FILE_EXT            ".rar"
#define     UBT_GZ_TAR_FILE_EXT         ".gz.tar"
#define     UBT_TAR_GZ_FILE_EXT         ".tar.gz"

#define UBX_MEMCPY_INC(t, s) memcpy(&t, s, sizeof(t));s+=sizeof(t);

#define SAFE_DELETE(p)       if(p){ delete p; p = NULL;}
#define SAFE_DELETE_ARRAY(p) if(p){ delete [] p; p = NULL;}


typedef struct _OtaMessage
{
    long type;
    emResultState eState;
}OtaMessage;

class QMovie;
class Mainwindow : public QWidget
{
    Q_OBJECT
public:
    explicit Mainwindow(QWidget *parent = 0);
    ~Mainwindow();

    QString getCurVersion();
    /**************************************************************************
    * 函数名: CompareVersion
    * 功能: 比较版本大小
    * 参数: [@in] strVersion1
    * 参数: [@in] strVersion2
    * 返回值: strVersion1 >  strVersion2 返回1
    *        strVersion1 <  strVersion2 返回-1
    *        strVersion1 =  strVersion2 返回0
    * 时间:2020/06/22
    * 作者: Joker
    */
    int CompareVersion(QString strVersion1, QString strVersion2);

    std::string read(const std::string &filePath);
    bool initOtaWindowsMsg();
    void sendOtaWindowsMsg(emResultState eState);
public slots:
    void onShowWinMsg(emResultState eState);
    void onUpgradeFail();
    void onShowCloseTips();
    void onTipsClose(bool bState);
private slots:
    void showDialog();

    void on_pbUpgrade_clicked();

    void on_pBNext_clicked();

    void on_pBEnterUpdatePage_clicked();

    void on_pbEnter_clicked();

    void on_pBImport_clicked();

private:
    Ui::Mainwindow *ui;
    titlebar *m_titlebar;
    dialog *m_dialog;
    tempmask *m_mask;
    OtaCloseGuide * m_pCloseTips;

    bool m_bLeftDown;
    QPoint m_ptPre;//记录前一点，实现窗体移动
    bool m_bIsImport;
    QString m_strFilePath;
    int m_nMsgId;
    QMovie * m_pMovie;
    bool m_bIsCloseTipsState;

protected:

    /**************************************************************************
    * 函数名: mousePressEvent
    * 功能: 鼠标按下事件
    */
    void mousePressEvent(QMouseEvent *e);

    /**************************************************************************
    * 函数名: mouseMoveEvent
    * 功能:鼠标移动事件
    */
    void mouseMoveEvent(QMouseEvent *e);

    /**************************************************************************
    * 函数名: mouseReleaseEvent
    * 功能: 鼠标离开事件
    */
    void mouseReleaseEvent(QMouseEvent *e);
};

#endif // MAINWINDOW_H
