#include "widget.h"
#include "ui_widget.h"
#include <QSerialPortInfo>
#include <QMessageBox>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QStringList serialNamePort;

    serilaPort = new QSerialPort(this);

    connect(serilaPort,SIGNAL(readyRead()),this,SLOT(serilaPortReadyRead_Slot()));

    foreach (const QSerialPortInfo &info ,QSerialPortInfo::availablePorts()) {
        serialNamePort<<info.portName();
    }
    ui->seialCb->addItems(serialNamePort);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::serilaPortReadyRead_Slot()
{
   QString buf;
   buf = QString(serilaPort->readAll());
   ui->recvEdit->appendPlainText(buf);

}


void Widget::on_openBt_clicked()
{
    QSerialPort::BaudRate baudRate;
    QSerialPort::DataBits dataBits;
    QSerialPort::StopBits stopBits;
    QSerialPort::Parity checkBits;

    if(ui->baundrateCb->currentText() == "4800"){
        baudRate = QSerialPort::Baud4800;
    }else if(ui->baundrateCb->currentText() == "9600"){
         baudRate = QSerialPort::Baud9600;
    }else if(ui->baundrateCb->currentText() == "115200"){
         baudRate = QSerialPort::Baud115200;
    }

    if(ui->dateCb->currentText() == "5"){
        dataBits = QSerialPort::Data5;
    }else if(ui->dateCb->currentText() == "6"){
        dataBits = QSerialPort::Data6;
    }else if(ui->dateCb->currentText() == "7"){
        dataBits = QSerialPort::Data7;
    }else if(ui->dateCb->currentText() == "8"){
        dataBits = QSerialPort::Data8;
    }

    if(ui->stopCb->currentText() == "1"){
       stopBits = QSerialPort::OneStop;
    }else if(ui->stopCb->currentText() == "1.5"){
       stopBits = QSerialPort::OneAndHalfStop;
    }else if(ui->stopCb->currentText() == "2"){
       stopBits = QSerialPort::TwoStop;
    }

    if(ui->checkCb->currentText() == "none"){
        checkBits = QSerialPort::NoParity;
    }

    serilaPort->setPortName(ui->seialCb->currentText());
    serilaPort->setBaudRate(baudRate);
    serilaPort->setDataBits(dataBits);
    serilaPort->setStopBits(stopBits);
    serilaPort->setParity(checkBits);

    if(serilaPort->open(QIODevice::ReadWrite) == true){
        QMessageBox::information(this,"提示","成功");
    }else{
        QMessageBox::critical(this,"提示","失败");
    }

}

void Widget::on_closeBt_clicked()
{
    serilaPort->close();
}

void Widget::on_sendBt_clicked()
{
    serilaPort->write(ui->sendEdit->text().toLocal8Bit().data());
}

void Widget::on_clearBt_clicked()
{
    ui->recvEdit->clear();
}
