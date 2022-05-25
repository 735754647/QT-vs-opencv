#include "VAbout.h"
#include "ui_VAbout.h"
#include <QDateTime>
#include <QDebug>
#include <QApplication>

VAbout::VAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VAbout)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::WindowContextHelpButtonHint,false);

    ui->label_info->setText(QString("软件版本:%1 更新日期:%2 作者:我是唐").arg(qApp->applicationVersion())
                            .arg(qApp->property("UpdateDateTime").toString()));

//    //禁止选中文本
//    ui->textBrowser->setTextInteractionFlags(Qt::NoTextInteraction);
}

VAbout::~VAbout()
{
    delete ui;
}

void VAbout::on_pushButton_clicked(bool checked)
{
    if(checked){
        ui->pushButton->setText(tr("返回"));
        ui->stackedWidget->setCurrentIndex(1);
    }else{
        ui->pushButton->setText(tr("交流"));
        ui->stackedWidget->setCurrentIndex(0);
    }
}
