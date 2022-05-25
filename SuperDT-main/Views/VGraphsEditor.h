#ifndef VGRAPHSEDITOR_H
#define VGRAPHSEDITOR_H

#include <QWidget>

namespace Ui {
class VGraphsEditor;
}

class VGraphsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit VGraphsEditor(QWidget *parent = 0);
    ~VGraphsEditor();

private:
    Ui::VGraphsEditor *ui;
};

#endif // VGRAPHSEDITOR_H
