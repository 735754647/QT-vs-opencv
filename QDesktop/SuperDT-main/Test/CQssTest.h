#ifndef CQSSTEST_H
#define CQSSTEST_H

#include <QDialog>

namespace Ui {
class CQssTest;
}

class CQssTest : public QDialog
{
    Q_OBJECT

public:
    explicit CQssTest(QWidget *parent = nullptr);
    ~CQssTest();

private slots:
    void on_pushButton_apply_clicked();

    void on_pushButton_choose_clicked();

    void on_pushButton_read_clicked();

private:
    Ui::CQssTest *ui;
};

#endif // CQSSTEST_H
