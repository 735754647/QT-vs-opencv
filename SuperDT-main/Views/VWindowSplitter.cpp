#include "VWindowSplitter.h"

VWindowSplitter::VWindowSplitter(QWidget *parent)
    : VBaseSplitter(parent)
{

}

QWidget *VWindowSplitter::newForm(QWidget *parent)
{
    return new VSession(parent);
}
