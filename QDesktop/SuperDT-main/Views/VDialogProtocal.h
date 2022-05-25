#ifndef VDIALOGPROTOCAL_H
#define VDIALOGPROTOCAL_H

#include <QDialog>

namespace Ui {
class VDialogProtocal;
}

class VDialogProtocal : public QDialog
{
    Q_OBJECT

public:
    explicit VDialogProtocal(QWidget *parent = 0);
    ~VDialogProtocal();

private:
    Ui::VDialogProtocal *ui;
};

#endif // VDIALOGPROTOCAL_H
