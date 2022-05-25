/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout_2;
    QPlainTextEdit *recvEdit;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QComboBox *seialCb;
    QLabel *label;
    QComboBox *baundrateCb;
    QLabel *label_2;
    QComboBox *dateCb;
    QLabel *label_3;
    QComboBox *stopCb;
    QLabel *label_4;
    QComboBox *checkCb;
    QLabel *label_5;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QLabel *label_6;
    QLineEdit *sendEdit;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *openBt;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *closeBt;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *sendBt;
    QSpacerItem *horizontalSpacer;
    QPushButton *clearBt;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(800, 480);
        gridLayout_2 = new QGridLayout(Widget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        recvEdit = new QPlainTextEdit(Widget);
        recvEdit->setObjectName(QStringLiteral("recvEdit"));
        QFont font;
        font.setPointSize(9);
        recvEdit->setFont(font);
        recvEdit->setReadOnly(true);

        gridLayout_2->addWidget(recvEdit, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        seialCb = new QComboBox(Widget);
        seialCb->setObjectName(QStringLiteral("seialCb"));

        gridLayout->addWidget(seialCb, 0, 0, 1, 1);

        label = new QLabel(Widget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 1, 1, 1);

        baundrateCb = new QComboBox(Widget);
        baundrateCb->addItem(QString());
        baundrateCb->addItem(QString());
        baundrateCb->addItem(QString());
        baundrateCb->setObjectName(QStringLiteral("baundrateCb"));

        gridLayout->addWidget(baundrateCb, 1, 0, 1, 1);

        label_2 = new QLabel(Widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 1, 1, 1);

        dateCb = new QComboBox(Widget);
        dateCb->addItem(QString());
        dateCb->addItem(QString());
        dateCb->addItem(QString());
        dateCb->addItem(QString());
        dateCb->setObjectName(QStringLiteral("dateCb"));

        gridLayout->addWidget(dateCb, 2, 0, 1, 1);

        label_3 = new QLabel(Widget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 1, 1, 1);

        stopCb = new QComboBox(Widget);
        stopCb->addItem(QString());
        stopCb->addItem(QString());
        stopCb->addItem(QString());
        stopCb->setObjectName(QStringLiteral("stopCb"));

        gridLayout->addWidget(stopCb, 3, 0, 1, 1);

        label_4 = new QLabel(Widget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 1, 1, 1);

        checkCb = new QComboBox(Widget);
        checkCb->addItem(QString());
        checkCb->setObjectName(QStringLiteral("checkCb"));

        gridLayout->addWidget(checkCb, 4, 0, 1, 1);

        label_5 = new QLabel(Widget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 4, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(150, 80));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(60, 30, 431, 31));
        QFont font1;
        font1.setPointSize(22);
        label_6->setFont(font1);
        label_6->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(groupBox);

        sendEdit = new QLineEdit(Widget);
        sendEdit->setObjectName(QStringLiteral("sendEdit"));

        verticalLayout_2->addWidget(sendEdit);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        openBt = new QPushButton(Widget);
        openBt->setObjectName(QStringLiteral("openBt"));

        horizontalLayout_6->addWidget(openBt);

        horizontalSpacer_3 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);

        closeBt = new QPushButton(Widget);
        closeBt->setObjectName(QStringLiteral("closeBt"));

        horizontalLayout_6->addWidget(closeBt);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);

        sendBt = new QPushButton(Widget);
        sendBt->setObjectName(QStringLiteral("sendBt"));

        horizontalLayout_6->addWidget(sendBt);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        clearBt = new QPushButton(Widget);
        clearBt->setObjectName(QStringLiteral("clearBt"));

        horizontalLayout_6->addWidget(clearBt);


        verticalLayout_2->addLayout(horizontalLayout_6);


        horizontalLayout->addLayout(verticalLayout_2);


        gridLayout_2->addLayout(horizontalLayout, 1, 0, 1, 1);


        retranslateUi(Widget);

        baundrateCb->setCurrentIndex(2);
        dateCb->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        label->setText(QApplication::translate("Widget", "\344\270\262\345\217\243\345\217\267", nullptr));
        baundrateCb->setItemText(0, QApplication::translate("Widget", "4800", nullptr));
        baundrateCb->setItemText(1, QApplication::translate("Widget", "9600", nullptr));
        baundrateCb->setItemText(2, QApplication::translate("Widget", "115200", nullptr));

        label_2->setText(QApplication::translate("Widget", "\346\263\242\347\211\271\347\216\207", nullptr));
        dateCb->setItemText(0, QApplication::translate("Widget", "5", nullptr));
        dateCb->setItemText(1, QApplication::translate("Widget", "6", nullptr));
        dateCb->setItemText(2, QApplication::translate("Widget", "7", nullptr));
        dateCb->setItemText(3, QApplication::translate("Widget", "8", nullptr));

        label_3->setText(QApplication::translate("Widget", "\346\225\260\346\215\256\344\275\215", nullptr));
        stopCb->setItemText(0, QApplication::translate("Widget", "1", nullptr));
        stopCb->setItemText(1, QApplication::translate("Widget", "1.5", nullptr));
        stopCb->setItemText(2, QApplication::translate("Widget", "2", nullptr));

        label_4->setText(QApplication::translate("Widget", "\345\201\234\346\255\242\344\275\215", nullptr));
        checkCb->setItemText(0, QApplication::translate("Widget", "none", nullptr));

        label_5->setText(QApplication::translate("Widget", "\346\240\241\351\252\214\344\275\215", nullptr));
        groupBox->setTitle(QString());
        label_6->setText(QApplication::translate("Widget", "\350\207\252\345\210\266\344\270\262\345\217\243\345\212\251\346\211\213", nullptr));
        openBt->setText(QApplication::translate("Widget", "\346\211\223\345\274\200", nullptr));
        closeBt->setText(QApplication::translate("Widget", "\345\205\263\351\227\255", nullptr));
        sendBt->setText(QApplication::translate("Widget", "\345\217\221\351\200\201", nullptr));
        clearBt->setText(QApplication::translate("Widget", "\346\270\205\347\251\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
