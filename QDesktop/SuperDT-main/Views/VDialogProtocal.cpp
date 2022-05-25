#include "VDialogProtocal.h"
#include "ui_VDialogProtocal.h"

VDialogProtocal::VDialogProtocal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VDialogProtocal)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::WindowContextHelpButtonHint,false);
}

VDialogProtocal::~VDialogProtocal()
{
    delete ui;
}
