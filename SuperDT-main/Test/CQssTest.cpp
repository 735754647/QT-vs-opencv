#include "CQssTest.h"
#include "ui_CQssTest.h"
#include <QFileDialog>

CQssTest::CQssTest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CQssTest)
{
    ui->setupUi(this);
}

CQssTest::~CQssTest()
{
    delete ui;
}

void CQssTest::on_pushButton_apply_clicked()
{
    qApp->setStyleSheet(ui->textBrowser->toPlainText());
}

void CQssTest::on_pushButton_choose_clicked()
{
    QString strFile = QFileDialog::getOpenFileName(this,
                       tr("Open Qss"), QApplication::applicationDirPath() + "../../", tr("Qss Files (*.*)"));

    ui->lineEdit_qss_file->setText(strFile);
    QFile file(strFile);
    if(file.open(QIODevice::ReadOnly)){
        ui->textBrowser->setText(file.readAll());
    }else{
        ui->textBrowser->setText("文件读取失败！！！");
    }

}

void CQssTest::on_pushButton_read_clicked()
{
    QFile file(ui->lineEdit_qss_file->text());
    if(file.open(QIODevice::ReadOnly)){
        ui->textBrowser->setText(file.readAll());
    }else{
        ui->textBrowser->setText("文件读取失败！！！");
    }

    on_pushButton_apply_clicked();
}
