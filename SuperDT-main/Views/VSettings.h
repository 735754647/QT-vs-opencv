#ifndef VSETTINGS_H
#define VSETTINGS_H

#include <QDialog>
#include <QSettings>


namespace Ui {
class VSettings;
}

class VSettings : public QDialog
{
    Q_OBJECT

public:
    explicit VSettings(QWidget *parent = nullptr);
    ~VSettings();


    void readSettings();

    void loadSysFont(); //加载系统字体
protected:
    void closeEvent(QCloseEvent *);
private:
    void resetFont();
private slots:
    void on_radioButton_zn_clicked(bool checked);

    void on_radioButton_english_clicked(bool checked);

    void on_spinBox_port_valueChanged(int arg1);

    void on_comboBox_text_code_currentTextChanged(const QString &arg1);

    void on_spinBox_maxline_valueChanged(int arg1);

    void on_spinBox_span_valueChanged(int arg1);

private:
    Ui::VSettings *ui;

    QSettings *m_pSetting = nullptr;

};

#endif // VSETTINGS_H
