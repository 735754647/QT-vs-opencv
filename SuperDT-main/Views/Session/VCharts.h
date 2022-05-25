#ifndef VCHARTS_H
#define VCHARTS_H

#include <QWidget>
#include "qcustomplot.h"
//#include <QMenu>

namespace Ui {
class VCharts;
}

class VCharts : public QCustomPlot
{
    Q_OBJECT

public:
    explicit VCharts(QWidget *parent = nullptr);
    ~VCharts();
    void init();
    void dataArrive(QString strIp, quint16 nPort, QByteArray byteTmp);
protected:
    void contextMenuEvent(QContextMenuEvent *event);
private slots:
    void on_pushButton_start_toggled(bool checked);

private:
    Ui::VCharts *ui;

    bool m_bAutoScale = true;
    bool m_bStop;
    QMenu *m_pMenu = nullptr;
    QBuffer m_bufCache;

    QAction *m_pActionStop = nullptr;
};

#endif // VCHARTS_H
