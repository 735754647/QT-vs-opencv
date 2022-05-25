#include "VBaseSplitterForm.h"
#include <QEvent>

VBaseSplitterForm::VBaseSplitterForm(QWidget *parent)
    : QWidget(parent)
{

}

void VBaseSplitterForm::recursiveInstallEventFilter(QObject *pObject)
{
    if(pObject->children().count() > 0) {
        foreach (QObject *objChild, pObject->children()) {
            if(objChild->isWidgetType()){
                objChild->installEventFilter(this);
                recursiveInstallEventFilter(objChild);
            }
        }
    }
}

void VBaseSplitterForm::showEvent(QShowEvent *event)
{
    recursiveInstallEventFilter(this);
}

bool VBaseSplitterForm::eventFilter(QObject *watched, QEvent *event)
{
    if(QEvent::MouseButtonPress == event->type()){
        emit sigFormSelected();
    }
    return QObject::eventFilter(watched,event);
}
