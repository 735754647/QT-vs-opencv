#ifndef VDIALOGSKIN_H
#define VDIALOGSKIN_H

#include <QDialog>
#include <QFile>
#include <QButtonGroup>

namespace Ui {
class VDialogSkin;
}

class VDialogSkin : public QDialog
{
    Q_OBJECT

public:
    explicit VDialogSkin(QWidget *parent = nullptr);
    ~VDialogSkin();

private slots:
    void on_pushButton_clicked();

private:
    Ui::VDialogSkin *ui;
    QFile *m_pFile = nullptr;
    QString m_strStyleSheet;
    QButtonGroup *m_pBtnGp = nullptr;
    int m_nCheckedId;
};

#endif // VDIALOGSKIN_H
