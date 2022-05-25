#ifndef VBASESPLITTER_H
#define VBASESPLITTER_H

#include <QSplitter>
#include <QHBoxLayout>
#include <QApplication>
#include <QDebug>
#include <QMouseEvent>
#include "VBaseSplitterForm.h"

class VBaseSplitter : public QWidget
{
    Q_OBJECT
public:
    explicit VBaseSplitter(QWidget *parent = 0);

    QWidget *selected(){return m_pSelectedForm;}
signals:
    void sigNewForm(QWidget *newForm); //新建了一个控件
    void sigSelected(QWidget *selectedForm);  //选中了一个控件
protected:
    virtual QWidget *newForm(QWidget *parent);//继承时可重写 添加组件函数 实现自定义控件分屏
    virtual void showEvent(QShowEvent *event);

private:
    void initUI(); // 不在构造函数调用 延迟到show的时候调用 避免继承时父类构造调用到父类newForm()
    QSplitter *creatSplitter(Qt::Orientation orientation,QWidget *parent);
    QWidget *creatForm(QWidget *parent);

    void removeForm(QWidget *rmForm);
    void removeSplitter(QSplitter *rmSplitter);

public slots:
    void slotVSplitScreen(); //垂直分屏
    void slotHSplitScreen(); //水平分屏
    void slotMergeScreen();  //并且
public:
    QList<QWidget *> m_listForm;
private:
    bool m_bIsInit = false;
    QList<QSplitter *> m_plistSplitter;
    QWidget *m_pSelectedForm = nullptr;

    QWidget *m_pGrandgrandfather = nullptr;
    QSplitter *m_pParentSplitter = nullptr;
    QSplitter *m_pGrandpaSplitter = nullptr;
    QWidget *m_pBrotherTextEditor = nullptr;
    QSplitter *m_pUncleSplitter = nullptr;

    QSplitter *m_pSplitterMain = nullptr;
    QWidget *m_pFormMain = nullptr;
};

#endif // VBASESPLITTER_H
