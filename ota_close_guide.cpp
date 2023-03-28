#include "ota_close_guide.h"
#include "ui_ota_close_guide.h"
#include <QStyleOption>
#include <QPainter>
#include <QBitmap>

OtaCloseGuide::OtaCloseGuide(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OtaCloseGuide)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_StyledBackground);
    this->setGeometry(1,51,618,448);
    this->setStyleSheet("#OtaCloseGuide{background-color:rgba(23,26,45,74%)}");
    ui->widget_5->setStyleSheet("background:#FFFFFF;border-radius:10px;");
    ui->pbcancel->setStyleSheet("background: #9EB2C0;border-radius: 5px;color:#FFFFFF");
    ui->pbok->setStyleSheet("background: #389FF1;border-radius: 5px;color:#FFFFFF");
    ui->label_2->setStyleSheet("font-family: PingFangSC-Medium;font-size: 14px;color: #4C545B;line-height: 24px;");
    hide();

//    if(parent)
//    {
//        move(parent->width()/2 - this->width()/2, parent->height()/2 - this->height()/2);
//    }

}

OtaCloseGuide::~OtaCloseGuide()
{
    delete ui;
}


void OtaCloseGuide::on_pbok_clicked()
{
    emit sigClose(true);
}

void OtaCloseGuide::on_pbcancel_clicked()
{
    emit sigClose(false);
}
