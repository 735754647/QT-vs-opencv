#ifndef VWINDOWSPLITTER_H
#define VWINDOWSPLITTER_H

#include <QWidget>
#include "VSession.h"
#include "VBaseSplitter.h"

class VWindowSplitter : public VBaseSplitter
{
    Q_OBJECT
public:
    explicit VWindowSplitter(QWidget *parent = nullptr);

protected:
    virtual QWidget *newForm(QWidget *parent) override;
};

#endif // VWINDOWSPLITTER_H
