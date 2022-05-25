#ifndef VABOUT_H
#define VABOUT_H

#include <QDialog>

namespace Ui {
class VAbout;
}

class VAbout : public QDialog
{
    Q_OBJECT

public:
    explicit VAbout(QWidget *parent = nullptr);
    ~VAbout();
private slots:
    void on_pushButton_clicked(bool checked);

private:
    Ui::VAbout *ui;
};

#endif // VABOUT_H
