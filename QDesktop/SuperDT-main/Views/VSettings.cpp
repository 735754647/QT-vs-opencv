#include "VSettings.h"
#include "ui_VSettings.h"
#include "CSettings.h"
#include <QMessageBox>
#include <QDebug>
#include "CUIHelper.h"
#include "CMainWindow.h"
#include <QFontDatabase>
#include <QListWidget>
#include <QTime>
#include <QTimer>
#include "VToast.h"

VSettings::VSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VSettings)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::WindowContextHelpButtonHint,false);

    m_pSetting = CSettings::getInstance()->settings();
    //异步初始化
    QTimer::singleShot(20,this,[=]{
        loadSysFont(); //获取字体 比较耗时
        readSettings();
        connect(ui->comboBox_chinese, static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
             [=](const QString &text){
            Q_UNUSED(text)
            resetFont();
        });
        connect(ui->comboBox_english, static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged),
             [=](const QString &text){
            Q_UNUSED(text)
            resetFont();
        });
        connect(ui->spinBox_font_size, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
              [=](int i){
            Q_UNUSED(i)
            resetFont();
        });
    });
}

VSettings::~VSettings()
{
    delete ui;
}

void VSettings::readSettings()
{
    ui->spinBox_port->setValue(m_pSetting->value("Setting/DefaultPort").toInt());
    ui->comboBox_text_code->setCurrentText(m_pSetting->value("Setting/TextCode").toString());
    ui->spinBox_maxline->setValue(m_pSetting->value("Setting/MaxLine").toInt());
    ui->spinBox_span->setValue(m_pSetting->value("Setting/Span").toInt());

    QString strLanguage = m_pSetting->value("Setting/Language").toString();
    if("简体中文" == strLanguage) {
        ui->radioButton_zn->setChecked(true);
    } else if("English" == strLanguage) {
        ui->radioButton_english->setChecked(true);
    }

    //外观
    QStringList strListFont = m_pSetting->value("Setting/Font").toString().split(',');
    if(!strListFont.isEmpty()){
        ui->comboBox_english->setCurrentText(strListFont.first());
        ui->comboBox_chinese->setCurrentText(strListFont.last());
    }
    ui->spinBox_font_size->setValue(m_pSetting->value("Setting/FontSize").toInt());
}

//void VSettings::writeSettings()
void VSettings::loadSysFont()
{
    QStringList strErrorFont; //不可用的字体
    strErrorFont<<"Fixedsys"<<"Terminal"<<"MS Sans Serif"<<"MS Serif"<<"Small Fonts"<<"System";
    QFontDatabase fontData;
    //中文字体选择框
    QListWidget *pListWidget = new QListWidget(this);
    foreach(QString strFont,fontData.families(QFontDatabase::SimplifiedChinese)){
        if(strErrorFont.contains(strFont))
            continue ;
        QListWidgetItem *pItem = new QListWidgetItem(strFont,pListWidget);
        pItem->setFont(QFont(strFont));
        pListWidget->addItem(pItem);
    }
    ui->comboBox_chinese->setModel(pListWidget->model());
    ui->comboBox_chinese->setView(pListWidget);


    //英文字体选择框
    QListWidget *pListWidgetE = new QListWidget(this);
    foreach(QString strFont,fontData.families(QFontDatabase::Latin)){
        if(strErrorFont.contains(strFont))
            continue ;
        QListWidgetItem *pItem = new QListWidgetItem(strFont,pListWidgetE);
        pItem->setFont(QFont(strFont));
        pListWidgetE->addItem(pItem);
    }
    ui->comboBox_english->setModel(pListWidgetE->model());
    ui->comboBox_english->setView(pListWidgetE);
}

void VSettings::closeEvent(QCloseEvent *)
{
    hide();
}

void VSettings::resetFont()
{
    //多个字体 首先会在第一个字体中寻找 依次往后
    QFont font = QApplication::font();
    font.setFamily(QString("%1,%2").arg(ui->comboBox_english->currentText())
                   .arg(ui->comboBox_chinese->currentText()));
    font.setPixelSize(ui->spinBox_font_size->value());
//    QApplication::setFont(QFont(),"QObject");
    QApplication::setFont(font,"QObject");
    qInfo()<<"重置字体:"<<font.family()<<font.pixelSize();

    m_pSetting->setValue("Setting/Font",QString("%1,%2")
                         .arg(ui->comboBox_english->currentText())
                         .arg(ui->comboBox_chinese->currentText()));

    m_pSetting->setValue("Setting/FontSize",ui->spinBox_font_size->text());
}

void VSettings::on_radioButton_zn_clicked(bool checked)
{
    Q_UNUSED(checked)
    m_pSetting->setValue("Setting/Language","简体中文");
    VToast::getInstance()->show(tr("重启生效"));
}

void VSettings::on_radioButton_english_clicked(bool checked)
{
    Q_UNUSED(checked)
    m_pSetting->setValue("Setting/Language","English");
    VToast::getInstance()->show(tr("重启生效"));
}

void VSettings::on_spinBox_port_valueChanged(int arg1)
{
    m_pSetting->setValue("Setting/DefaultPort",arg1);
}

void VSettings::on_comboBox_text_code_currentTextChanged(const QString &arg1)
{
    m_pSetting->setValue("Setting/TextCode",arg1);
    CMainWindow::getInstance()->slotTextCode(arg1);
}

void VSettings::on_spinBox_maxline_valueChanged(int arg1)
{
    m_pSetting->setValue("Setting/MaxLine",arg1);
}

void VSettings::on_spinBox_span_valueChanged(int arg1)
{
    m_pSetting->setValue("Setting/Span",arg1);
}
