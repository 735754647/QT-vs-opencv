#include "VDialogAscii.h"
#include "ui_VDialogAscii.h"
#include <QHeaderView>
#include <QTableView>
#include <QTableWidgetItem>
#include "CConversion.h"
#include <QDebug>

VDialogAscii::VDialogAscii(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VDialogAscii)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::WindowContextHelpButtonHint,false);

    listTable<<ui->tableWidget<<ui->tableWidget_2
              <<ui->tableWidget_3<<ui->tableWidget_4<<ui->tableWidget_5<<ui->tableWidget_6;

    int nRowCount = 128 / listTable.size() + 1;

    foreach (QTableWidget *pTableWidget, listTable) {
        pTableWidget->setRowCount(nRowCount);
        pTableWidget->setStyleSheet("font-size:14px;");
        pTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        pTableWidget->resizeColumnsToContents();
        pTableWidget->resizeRowsToContents();
    }

    QStringList strListText;
    strListText<<"NUL"<<"SOH"<<"STX"<<"ETX"<<"EOT"<<"ENQ"<<"ACK"<<"BEL"<<"BS"<<"HT"<<"LF"<<"VT"<<"FF"<<"CR"<<"SO"<<"SI"<<"DLE"<<"DC1"<<"DC2"<<"DC3"<<"DC4"<<"NAK"<<"SYN"<<"ETB"<<"CAN"<<"EM"<<"SUB"<<"ESC"<<"FS"<<"GS"<<"RS"<<"US"<<"DEL";
    for(int i = 0; i < 128; i++) {
        /*unsigned*/ char val = i;
        listTable[i/nRowCount]->setItem(i%nRowCount,0,new QTableWidgetItem(QString::number(i))); //十进制
        listTable[i/nRowCount]->setItem(i%nRowCount,1,new QTableWidgetItem(QString("%1").arg(i,4,16,QLatin1Char('0')))); //十六进制
        QString strText(val);
        if(strText.isEmpty()){
            qDebug()<<"空："<<i;
        }
        if(i < 32)
            listTable[i/nRowCount]->setItem(i%nRowCount,2,new QTableWidgetItem(strListText[i])); //字符串
        else if(i == 127)
            listTable[i/nRowCount]->setItem(i%nRowCount,2,new QTableWidgetItem(strListText.last())); //字符串
        else
            listTable[i/nRowCount]->setItem(i%nRowCount,2,new QTableWidgetItem(QString(val))); //字符串
    }
}

VDialogAscii::~VDialogAscii()
{
    delete ui;
}
