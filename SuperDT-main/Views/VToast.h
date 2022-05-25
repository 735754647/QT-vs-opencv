#ifndef VTOAST_H
#define VTOAST_H

#include <QDialog>
#include <QLabel>
#include <QHBoxLayout>

class VToast : public QDialog
{
    Q_OBJECT
    explicit VToast(QWidget *parent = 0);
public:
    static VToast *getInstance();

    void show(QString strText);
private:
    QLabel *m_pIconLabel = nullptr;
    QLabel *m_pHintLabel = nullptr;
};

#endif // VTOAST_H
