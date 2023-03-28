#ifndef TEMPMASK_H
#define TEMPMASK_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class tempmask;
}
enum emResultState
{
    Idle = 0,               // 空闲状态
    UpdateSuccess = 1,      // 升级成功
    RestoreSuccess = 2,     // 恢复成功
    UpdateImageError = 3,	// 升级镜像错误
    RestoreImageError = 4,  // 备份镜像错误
    Updating = 5,           // 升级中
    PowerKey = 6            // 按下电源键
};

class tempmask : public QWidget
{
    Q_OBJECT

public:
    explicit tempmask(QWidget *parent = 0);
    ~tempmask();
    void SetOtaFile(bool bDelt, QString strOtaFile);
    void setOtaResultState(char state);

public slots:
    void showMask();
    void UpgradeFail();
signals:
    void sigShowWinMsg(emResultState eState);
    void sigUpgradeFail();

private slots:
    void doUpgrade();
    void countdown();


private:
    Ui::tempmask *ui;
    QTimer *m_showTimer;
    int seconds;
    QString m_strOtaFile;
    bool m_bDelt;


};

#endif // TEMPMASK_H
