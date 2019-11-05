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
    QTextEdit *te_rmk1;
    QPushButton *pb_reset;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_dir;
    QLabel *label_offset;
    QLabel *label_strg;
    QLabel *label_exch;
    QLabel *label_symbol;
    QLabel *label_price;
    QLabel *label_qty;
    QVBoxLayout *verticalLayout;
    QComboBox *cb_Dir;
    QComboBox *cb_offset;
    QComboBox *cb_strg;
    QComboBox *cb_exch;
    QLineEdit *le_symbol;
    QLineEdit *le_price;
    QLineEdit *le_qty;
    QTextEdit *te_rmk2;
    QTextEdit *te_log;
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_rmk1;
    QLabel *label_rmk2;
    QLabel *label_log;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *OrderForm)
    {
        if (OrderForm->objectName().isEmpty())
            OrderForm->setObjectName(QString::fromUtf8("OrderForm"));
        OrderForm->resize(778, 521);
        centralwidget = new QWidget(OrderForm);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pb_order = new QPushButton(centralwidget);
        pb_order->setObjectName(QString::fromUtf8("pb_order"));
        pb_order->setGeometry(QRect(50, 300, 101, 21));
        te_rmk1 = new QTextEdit(centralwidget);
        te_rmk1->setObjectName(QString::fromUtf8("te_rmk1"));
        te_rmk1->setGeometry(QRect(380, 30, 211, 51));
        pb_reset = new QPushButton(centralwidget);
        pb_reset->setObjectName(QString::fromUtf8("pb_reset"));
        pb_reset->setGeometry(QRect(161, 300, 101, 21));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(60, 30, 212, 251));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_dir = new QLabel(layoutWidget);
        label_dir->setObjectName(QString::fromUtf8("label_dir"));

        verticalLayout_2->addWidget(label_dir);

        label_offset = new QLabel(layoutWidget);
        label_offset->setObjectName(QString::fromUtf8("label_offset"));

        verticalLayout_2->addWidget(label_offset);

        label_strg = new QLabel(layoutWidget);
        label_strg->setObjectName(QString::fromUtf8("label_strg"));

        verticalLayout_2->addWidget(label_strg);

        label_exch = new QLabel(layoutWidget);
        label_exch->setObjectName(QString::fromUtf8("label_exch"));

        verticalLayout_2->addWidget(label_exch);

        label_symbol = new QLabel(layoutWidget);
        label_symbol->setObjectName(QString::fromUtf8("label_symbol"));

        verticalLayout_2->addWidget(label_symbol);

        label_price = new QLabel(layoutWidget);
        label_price->setObjectName(QString::fromUtf8("label_price"));

        verticalLayout_2->addWidget(label_price);

        label_qty = new QLabel(layoutWidget);
        label_qty->setObjectName(QString::fromUtf8("label_qty"));

        verticalLayout_2->addWidget(label_qty);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        cb_Dir = new QComboBox(layoutWidget);
        cb_Dir->setObjectName(QString::fromUtf8("cb_Dir"));

        verticalLayout->addWidget(cb_Dir);

        cb_offset = new QComboBox(layoutWidget);
        cb_offset->setObjectName(QString::fromUtf8("cb_offset"));

        verticalLayout->addWidget(cb_offset);

        cb_strg = new QComboBox(layoutWidget);
        cb_strg->setObjectName(QString::fromUtf8("cb_strg"));

        verticalLayout->addWidget(cb_strg);

        cb_exch = new QComboBox(layoutWidget);
        cb_exch->setObjectName(QString::fromUtf8("cb_exch"));

        verticalLayout->addWidget(cb_exch);

        le_symbol = new QLineEdit(layoutWidget);
        le_symbol->setObjectName(QString::fromUtf8("le_symbol"));

        verticalLayout->addWidget(le_symbol);

        le_price = new QLineEdit(layoutWidget);
        le_price->setObjectName(QString::fromUtf8("le_price"));

        verticalLayout->addWidget(le_price);

        le_qty = new QLineEdit(layoutWidget);
        le_qty->setObjectName(QString::fromUtf8("le_qty"));

        verticalLayout->addWidget(le_qty);


        horizontalLayout->addLayout(verticalLayout);

        te_rmk2 = new QTextEdit(centralwidget);
        te_rmk2->setObjectName(QString::fromUtf8("te_rmk2"));
        te_rmk2->setGeometry(QRect(380, 100, 211, 51));
        te_log = new QTextEdit(centralwidget);
        te_log->setObjectName(QString::fromUtf8("te_log"));
        te_log->setGeometry(QRect(380, 160, 211, 51));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(290, 30, 82, 191));
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_rmk1 = new QLabel(widget);
        label_rmk1->setObjectName(QString::fromUtf8("label_rmk1"));

        verticalLayout_3->addWidget(label_rmk1);

        label_rmk2 = new QLabel(widget);
        label_rmk2->setObjectName(QString::fromUtf8("label_rmk2"));

        verticalLayout_3->addWidget(label_rmk2);

        label_log = new QLabel(widget);
        label_log->setObjectName(QString::fromUtf8("label_log"));

        verticalLayout_3->addWidget(label_log);

        OrderForm->setCentralWidget(centralwidget);
        menubar = new QMenuBar(OrderForm);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 778, 27));
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
        label_exch->setText(QApplication::translate("OrderForm", "Exchange", nullptr));
        label_symbol->setText(QApplication::translate("OrderForm", "Symbol", nullptr));
        label_price->setText(QApplication::translate("OrderForm", "Price", nullptr));
        label_qty->setText(QApplication::translate("OrderForm", "TextLabel", nullptr));
        label_rmk1->setText(QApplication::translate("OrderForm", "Remark1", nullptr));
        label_rmk2->setText(QApplication::translate("OrderForm", "Remark2", nullptr));
        label_log->setText(QApplication::translate("OrderForm", "Log Infor", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OrderForm: public Ui_OrderForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORDERFORM_H
