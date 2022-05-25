#ifndef VSESSION_H
#define VSESSION_H

#include <QWidget>
#include "VBaseSplitterForm.h"
#include "CConnectManager.h"
#include "IConnectInterface.h"

namespace Ui {
class VSession;
}

class VSession : public VBaseSplitterForm
{
    Q_OBJECT

public:
    explicit VSession(QWidget *parent = nullptr);
    ~VSession();

    bool isChecked(){return m_bChecked;}
    virtual void setFormChecked(bool bIsChecked);
private:
    Ui::VSession *ui;

    CConnectManager *m_pConnectManager = nullptr;
//    QVector<IConnectInterface*> m_vecSubscriber;
    bool m_bChecked;
};

#endif // VSESSION_H
