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
#include <QtWidgets/QGridLayout>
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
    QTextEdit *te_rmk2;
    QTextEdit *te_log;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_rmk2;
    QLabel *label_log;
    QLabel *label_rmk1;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout;
    QComboBox *cb_Dir;
    QComboBox *cb_offset;
    QComboBox *cb_strg;
    QComboBox *cb_exch;
    QLineEdit *le_symbol;
    QLineEdit *le_price;
    QLineEdit *le_qty;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *le_del;
    QLabel *label_del;
    QPushButton *pb_del;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *OrderForm)
    {
        if (OrderForm->objectName().isEmpty())
            OrderForm->setObjectName(QString::fromUtf8("OrderForm"));
        OrderForm->resize(945, 658);
        centralwidget = new QWidget(OrderForm);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pb_order = new QPushButton(centralwidget);
        pb_order->setObjectName(QString::fromUtf8("pb_order"));
        pb_order->setGeometry(QRect(550, 270, 171, 41));
        QFont font;
        font.setPointSize(20);
        pb_order->setFont(font);
        te_rmk1 = new QTextEdit(centralwidget);
        te_rmk1->setObjectName(QString::fromUtf8("te_rmk1"));
        te_rmk1->setGeometry(QRect(689, 49, 211, 51));
        te_rmk1->setFont(font);
        pb_reset = new QPushButton(centralwidget);
        pb_reset->setObjectName(QString::fromUtf8("pb_reset"));
        pb_reset->setGeometry(QRect(740, 270, 141, 41));
        pb_reset->setFont(font);
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(110, 10, 181, 560));
        layoutWidget->setFont(font);
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_dir = new QLabel(layoutWidget);
        label_dir->setObjectName(QString::fromUtf8("label_dir"));
        label_dir->setFont(font);

        verticalLayout_2->addWidget(label_dir);

        label_offset = new QLabel(layoutWidget);
        label_offset->setObjectName(QString::fromUtf8("label_offset"));
        label_offset->setFont(font);

        verticalLayout_2->addWidget(label_offset);

        label_strg = new QLabel(layoutWidget);
        label_strg->setObjectName(QString::fromUtf8("label_strg"));
        label_strg->setFont(font);

        verticalLayout_2->addWidget(label_strg);

        label_exch = new QLabel(layoutWidget);
        label_exch->setObjectName(QString::fromUtf8("label_exch"));
        label_exch->setFont(font);

        verticalLayout_2->addWidget(label_exch);

        label_symbol = new QLabel(layoutWidget);
        label_symbol->setObjectName(QString::fromUtf8("label_symbol"));
        label_symbol->setFont(font);

        verticalLayout_2->addWidget(label_symbol);

        label_price = new QLabel(layoutWidget);
        label_price->setObjectName(QString::fromUtf8("label_price"));
        label_price->setFont(font);

        verticalLayout_2->addWidget(label_price);

        label_qty = new QLabel(layoutWidget);
        label_qty->setObjectName(QString::fromUtf8("label_qty"));
        label_qty->setFont(font);

        verticalLayout_2->addWidget(label_qty);


        horizontalLayout->addLayout(verticalLayout_2);

        te_rmk2 = new QTextEdit(centralwidget);
        te_rmk2->setObjectName(QString::fromUtf8("te_rmk2"));
        te_rmk2->setGeometry(QRect(689, 109, 211, 51));
        te_rmk2->setFont(font);
        te_log = new QTextEdit(centralwidget);
        te_log->setObjectName(QString::fromUtf8("te_log"));
        te_log->setGeometry(QRect(689, 169, 211, 51));
        te_log->setFont(font);
        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(549, 49, 131, 191));
        layoutWidget1->setFont(font);
        verticalLayout_3 = new QVBoxLayout(layoutWidget1);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_rmk2 = new QLabel(centralwidget);
        label_rmk2->setObjectName(QString::fromUtf8("label_rmk2"));
        label_rmk2->setGeometry(QRect(560, 105, 112, 59));
        label_rmk2->setFont(font);
        label_log = new QLabel(centralwidget);
        label_log->setObjectName(QString::fromUtf8("label_log"));
        label_log->setGeometry(QRect(560, 170, 112, 59));
        label_log->setFont(font);
        label_rmk1 = new QLabel(centralwidget);
        label_rmk1->setObjectName(QString::fromUtf8("label_rmk1"));
        label_rmk1->setGeometry(QRect(560, 40, 112, 59));
        label_rmk1->setFont(font);
        layoutWidget2 = new QWidget(centralwidget);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(300, 10, 241, 558));
        layoutWidget2->setFont(font);
        verticalLayout = new QVBoxLayout(layoutWidget2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        cb_Dir = new QComboBox(layoutWidget2);
        cb_Dir->setObjectName(QString::fromUtf8("cb_Dir"));
        cb_Dir->setFont(font);

        verticalLayout->addWidget(cb_Dir);

        cb_offset = new QComboBox(layoutWidget2);
        cb_offset->setObjectName(QString::fromUtf8("cb_offset"));
        cb_offset->setFont(font);

        verticalLayout->addWidget(cb_offset);

        cb_strg = new QComboBox(layoutWidget2);
        cb_strg->setObjectName(QString::fromUtf8("cb_strg"));
        cb_strg->setFont(font);

        verticalLayout->addWidget(cb_strg);

        cb_exch = new QComboBox(layoutWidget2);
        cb_exch->setObjectName(QString::fromUtf8("cb_exch"));
        cb_exch->setFont(font);

        verticalLayout->addWidget(cb_exch);

        le_symbol = new QLineEdit(layoutWidget2);
        le_symbol->setObjectName(QString::fromUtf8("le_symbol"));
        le_symbol->setFont(font);

        verticalLayout->addWidget(le_symbol);

        le_price = new QLineEdit(layoutWidget2);
        le_price->setObjectName(QString::fromUtf8("le_price"));
        le_price->setFont(font);

        verticalLayout->addWidget(le_price);

        le_qty = new QLineEdit(layoutWidget2);
        le_qty->setObjectName(QString::fromUtf8("le_qty"));
        le_qty->setFont(font);

        verticalLayout->addWidget(le_qty);

        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(560, 360, 331, 131));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        le_del = new QLineEdit(gridLayoutWidget);
        le_del->setObjectName(QString::fromUtf8("le_del"));
        le_del->setFont(font);

        gridLayout->addWidget(le_del, 2, 0, 1, 1);

        label_del = new QLabel(gridLayoutWidget);
        label_del->setObjectName(QString::fromUtf8("label_del"));
        label_del->setFont(font);

        gridLayout->addWidget(label_del, 1, 0, 1, 1);

        pb_del = new QPushButton(gridLayoutWidget);
        pb_del->setObjectName(QString::fromUtf8("pb_del"));
        pb_del->setFont(font);

        gridLayout->addWidget(pb_del, 3, 0, 1, 1);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(570, 520, 311, 30));
        OrderForm->setCentralWidget(centralwidget);
        menubar = new QMenuBar(OrderForm);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 945, 27));
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
        label_qty->setText(QApplication::translate("OrderForm", "Qty", nullptr));
        label_rmk2->setText(QApplication::translate("OrderForm", "Remark2", nullptr));
        label_log->setText(QApplication::translate("OrderForm", "Log Infor", nullptr));
        label_rmk1->setText(QApplication::translate("OrderForm", "Remark1", nullptr));
        label_del->setText(QApplication::translate("OrderForm", "Delete Order ID", nullptr));
        pb_del->setText(QApplication::translate("OrderForm", "Delete", nullptr));
        pushButton->setText(QApplication::translate("OrderForm", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OrderForm: public Ui_OrderForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORDERFORM_H
