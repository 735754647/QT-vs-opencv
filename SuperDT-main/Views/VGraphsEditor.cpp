#include "VGraphsEditor.h"
#include "ui_VGraphsEditor.h"

VGraphsEditor::VGraphsEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VGraphsEditor)
{
    ui->setupUi(this);
}

VGraphsEditor::~VGraphsEditor()
{
    delete ui;
}
