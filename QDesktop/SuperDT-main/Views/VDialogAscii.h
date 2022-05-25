#ifndef VDIALOGASCII_H
#define VDIALOGASCII_H

#include <QDialog>
#include <QTableWidget>

namespace Ui {
class VDialogAscii;
}

class VDialogAscii : public QDialog
{
    Q_OBJECT

public:
    explicit VDialogAscii(QWidget *parent = 0);
    ~VDialogAscii();
private:
    Ui::VDialogAscii *ui;

    QList<QTableWidget*> listTable;
};

#endif // VDIALOGASCII_H
