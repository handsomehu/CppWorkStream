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
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OrderForm
{
public:
    QAction *actionCreate;
    QAction *actionRemove;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuTrade;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *OrderForm)
    {
        if (OrderForm->objectName().isEmpty())
            OrderForm->setObjectName(QString::fromUtf8("OrderForm"));
        OrderForm->resize(356, 311);
        actionCreate = new QAction(OrderForm);
        actionCreate->setObjectName(QString::fromUtf8("actionCreate"));
        actionRemove = new QAction(OrderForm);
        actionRemove->setObjectName(QString::fromUtf8("actionRemove"));
        centralwidget = new QWidget(OrderForm);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        OrderForm->setCentralWidget(centralwidget);
        menubar = new QMenuBar(OrderForm);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 356, 27));
        menuTrade = new QMenu(menubar);
        menuTrade->setObjectName(QString::fromUtf8("menuTrade"));
        OrderForm->setMenuBar(menubar);
        statusbar = new QStatusBar(OrderForm);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        OrderForm->setStatusBar(statusbar);

        menubar->addAction(menuTrade->menuAction());
        menuTrade->addAction(actionCreate);
        menuTrade->addAction(actionRemove);

        retranslateUi(OrderForm);

        QMetaObject::connectSlotsByName(OrderForm);
    } // setupUi

    void retranslateUi(QMainWindow *OrderForm)
    {
        OrderForm->setWindowTitle(QApplication::translate("OrderForm", "OrderForm", nullptr));
        actionCreate->setText(QApplication::translate("OrderForm", "Create Order and Log", nullptr));
        actionRemove->setText(QApplication::translate("OrderForm", "Remove Log", nullptr));
        menuTrade->setTitle(QApplication::translate("OrderForm", "Trade", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OrderForm: public Ui_OrderForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORDERFORM_H
