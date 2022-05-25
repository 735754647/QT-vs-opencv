#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSerialPort>
#include <Qstring>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QSerialPort *serilaPort;
private slots:
    void on_openBt_clicked();

    void on_closeBt_clicked();

    void serilaPortReadyRead_Slot();

    void on_sendBt_clicked();

    void on_clearBt_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
