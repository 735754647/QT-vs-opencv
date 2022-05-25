#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

namespace Ui {
class CMainWindow;
}

class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CMainWindow(QWidget *parent = nullptr);
    ~CMainWindow();

    static CMainWindow *getInstance();

public slots:
    void slotSendBytes(int nBytes);
    void slotRecvBytes(int nBytes);
    void slotTextCode(QString strTextCode);
signals:
    void sigRecount();
private:
    void initToolBar();
    void initStatusBar();
private:
    Ui::CMainWindow *ui;

    //状态栏
    QLabel *m_pTextCodeLabel = nullptr;
    QLabel *m_pSendLabel = nullptr;
    QLabel *m_pRecvLabel = nullptr;
    QPushButton *m_pBtnRecount = nullptr;

};

#endif // CMAINWINDOW_H
