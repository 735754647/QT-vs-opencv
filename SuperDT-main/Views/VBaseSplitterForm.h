#ifndef VBASESPLITTERFORM_H
#define VBASESPLITTERFORM_H

#include <QWidget>

class VBaseSplitterForm : public QWidget
{
    Q_OBJECT
public:
    explicit VBaseSplitterForm(QWidget *parent = nullptr);

    virtual void setFormChecked(bool bIsChecked) = 0; //实现选中和非选中的状态
    virtual bool isChecked() = 0;
private:
    void recursiveInstallEventFilter(QObject *pObject);
    virtual void showEvent(QShowEvent *event);
    virtual bool eventFilter(QObject *watched, QEvent *event);
signals:
    void sigFormSelected(); //当控件被选中时 用发出此信号
};

#endif // VBASESPLITTERFORM_H
