#ifndef OTA_CLOSE_GUIDE_H
#define OTA_CLOSE_GUIDE_H

#include <QDialog>

namespace Ui {
class OtaCloseGuide;
}

class OtaCloseGuide : public QWidget
{
    Q_OBJECT

public:
    explicit OtaCloseGuide(QWidget *parent = 0);
    ~OtaCloseGuide();
signals:
    void sigClose(bool bState);

private slots:

    void on_pbok_clicked();

    void on_pbcancel_clicked();

private:
    Ui::OtaCloseGuide *ui;
};

#endif // OTA_CLOSE_GUIDE_H
