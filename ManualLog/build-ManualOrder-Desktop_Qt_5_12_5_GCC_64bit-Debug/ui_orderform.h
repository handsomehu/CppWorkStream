/********************************************************************************
** Form generated from reading UI file 'orderform.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ORDERFORM_H
#define UI_ORDERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OrderForm
{
public:
    QWidget *centralwidget;
    QPushButton *pb_order;
    QTextEdit *te_infor;
    QPushButton *pb_reset;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_dir;
    QLabel *label_offset;
    QLabel *label_strg;
    QLabel *label_symbol;
    QLabel *label_price;
    QVBoxLayout *verticalLayout;
    QComboBox *cb_Dir;
    QComboBox *cb_offset;
    QComboBox *cb_strg;
    QLineEdit *le_symbol;
    QLineEdit *le_price;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *OrderForm)
    {
        if (OrderForm->objectName().isEmpty())
            OrderForm->setObjectName(QString::fromUtf8("OrderForm"));
        OrderForm->resize(630, 342);
        centralwidget = new QWidget(OrderForm);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pb_order = new QPushButton(centralwidget);
        pb_order->setObjectName(QString::fromUtf8("pb_order"));
        pb_order->setGeometry(QRect(59, 240, 101, 21));
        te_infor = new QTextEdit(centralwidget);
        te_infor->setObjectName(QString::fromUtf8("te_infor"));
        te_infor->setGeometry(QRect(410, 30, 211, 201));
        pb_reset = new QPushButton(centralwidget);
        pb_reset->setObjectName(QString::fromUtf8("pb_reset"));
        pb_reset->setGeometry(QRect(170, 240, 101, 21));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(60, 30, 212, 190));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_dir = new QLabel(widget);
        label_dir->setObjectName(QString::fromUtf8("label_dir"));

        verticalLayout_2->addWidget(label_dir);

        label_offset = new QLabel(widget);
        label_offset->setObjectName(QString::fromUtf8("label_offset"));

        verticalLayout_2->addWidget(label_offset);

        label_strg = new QLabel(widget);
        label_strg->setObjectName(QString::fromUtf8("label_strg"));

        verticalLayout_2->addWidget(label_strg);

        label_symbol = new QLabel(widget);
        label_symbol->setObjectName(QString::fromUtf8("label_symbol"));

        verticalLayout_2->addWidget(label_symbol);

        label_price = new QLabel(widget);
        label_price->setObjectName(QString::fromUtf8("label_price"));

        verticalLayout_2->addWidget(label_price);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        cb_Dir = new QComboBox(widget);
        cb_Dir->setObjectName(QString::fromUtf8("cb_Dir"));

        verticalLayout->addWidget(cb_Dir);

        cb_offset = new QComboBox(widget);
        cb_offset->setObjectName(QString::fromUtf8("cb_offset"));

        verticalLayout->addWidget(cb_offset);

        cb_strg = new QComboBox(widget);
        cb_strg->setObjectName(QString::fromUtf8("cb_strg"));

        verticalLayout->addWidget(cb_strg);

        le_symbol = new QLineEdit(widget);
        le_symbol->setObjectName(QString::fromUtf8("le_symbol"));

        verticalLayout->addWidget(le_symbol);

        le_price = new QLineEdit(widget);
        le_price->setObjectName(QString::fromUtf8("le_price"));

        verticalLayout->addWidget(le_price);


        horizontalLayout->addLayout(verticalLayout);

        OrderForm->setCentralWidget(centralwidget);
        menubar = new QMenuBar(OrderForm);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 630, 27));
        OrderForm->setMenuBar(menubar);
        statusbar = new QStatusBar(OrderForm);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        OrderForm->setStatusBar(statusbar);

        retranslateUi(OrderForm);

        QMetaObject::connectSlotsByName(OrderForm);
    } // setupUi

    void retranslateUi(QMainWindow *OrderForm)
    {
        OrderForm->setWindowTitle(QApplication::translate("OrderForm", "OrderForm", nullptr));
        pb_order->setText(QApplication::translate("OrderForm", "Order", nullptr));
        pb_reset->setText(QApplication::translate("OrderForm", "Reset", nullptr));
        label_dir->setText(QApplication::translate("OrderForm", "Direction", nullptr));
        label_offset->setText(QApplication::translate("OrderForm", "Offset", nullptr));
        label_strg->setText(QApplication::translate("OrderForm", "Strategy", nullptr));
        label_symbol->setText(QApplication::translate("OrderForm", "Symbol", nullptr));
        label_price->setText(QApplication::translate("OrderForm", "Price", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OrderForm: public Ui_OrderForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORDERFORM_H
