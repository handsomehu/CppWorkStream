/********************************************************************************
** Form generated from reading UI file 'createdlg.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEDLG_H
#define UI_CREATEDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_CreateDlg
{
public:
    QPushButton *pb_reset;
    QLabel *label_strg;
    QComboBox *cb_Dir;
    QLabel *label_qty;
    QLabel *label_offset;
    QTextEdit *te_log;
    QLineEdit *le_price;
    QLabel *label_exch;
    QComboBox *cb_strg;
    QLabel *label_price;
    QTextEdit *te_rmk1;
    QLabel *label_rmk1;
    QLabel *label_rmk2;
    QTextEdit *te_rmk2;
    QLineEdit *le_symbol;
    QLabel *label_dir;
    QLabel *label_log;
    QPushButton *pb_order;
    QComboBox *cb_exch;
    QLabel *label_symbol;
    QComboBox *cb_offset;
    QLineEdit *le_qty;
    QPushButton *pb_ctp;

    void setupUi(QDialog *CreateDlg)
    {
        if (CreateDlg->objectName().isEmpty())
            CreateDlg->setObjectName(QString::fromUtf8("CreateDlg"));
        CreateDlg->resize(944, 483);
        pb_reset = new QPushButton(CreateDlg);
        pb_reset->setObjectName(QString::fromUtf8("pb_reset"));
        pb_reset->setGeometry(QRect(740, 340, 141, 41));
        QFont font;
        font.setPointSize(20);
        pb_reset->setFont(font);
        label_strg = new QLabel(CreateDlg);
        label_strg->setObjectName(QString::fromUtf8("label_strg"));
        label_strg->setGeometry(QRect(30, 140, 141, 41));
        label_strg->setFont(font);
        cb_Dir = new QComboBox(CreateDlg);
        cb_Dir->setObjectName(QString::fromUtf8("cb_Dir"));
        cb_Dir->setGeometry(QRect(220, 20, 239, 38));
        cb_Dir->setFont(font);
        label_qty = new QLabel(CreateDlg);
        label_qty->setObjectName(QString::fromUtf8("label_qty"));
        label_qty->setGeometry(QRect(30, 370, 111, 41));
        label_qty->setFont(font);
        label_offset = new QLabel(CreateDlg);
        label_offset->setObjectName(QString::fromUtf8("label_offset"));
        label_offset->setGeometry(QRect(30, 80, 181, 31));
        label_offset->setFont(font);
        te_log = new QTextEdit(CreateDlg);
        te_log->setObjectName(QString::fromUtf8("te_log"));
        te_log->setGeometry(QRect(680, 170, 211, 101));
        te_log->setFont(font);
        le_price = new QLineEdit(CreateDlg);
        le_price->setObjectName(QString::fromUtf8("le_price"));
        le_price->setGeometry(QRect(220, 330, 239, 38));
        le_price->setFont(font);
        label_exch = new QLabel(CreateDlg);
        label_exch->setObjectName(QString::fromUtf8("label_exch"));
        label_exch->setGeometry(QRect(30, 200, 177, 41));
        label_exch->setFont(font);
        cb_strg = new QComboBox(CreateDlg);
        cb_strg->setObjectName(QString::fromUtf8("cb_strg"));
        cb_strg->setGeometry(QRect(220, 140, 239, 38));
        cb_strg->setFont(font);
        label_price = new QLabel(CreateDlg);
        label_price->setObjectName(QString::fromUtf8("label_price"));
        label_price->setGeometry(QRect(30, 320, 121, 41));
        label_price->setFont(font);
        te_rmk1 = new QTextEdit(CreateDlg);
        te_rmk1->setObjectName(QString::fromUtf8("te_rmk1"));
        te_rmk1->setGeometry(QRect(680, 20, 211, 51));
        te_rmk1->setFont(font);
        label_rmk1 = new QLabel(CreateDlg);
        label_rmk1->setObjectName(QString::fromUtf8("label_rmk1"));
        label_rmk1->setGeometry(QRect(510, 20, 112, 51));
        label_rmk1->setFont(font);
        label_rmk2 = new QLabel(CreateDlg);
        label_rmk2->setObjectName(QString::fromUtf8("label_rmk2"));
        label_rmk2->setGeometry(QRect(510, 80, 112, 41));
        label_rmk2->setFont(font);
        te_rmk2 = new QTextEdit(CreateDlg);
        te_rmk2->setObjectName(QString::fromUtf8("te_rmk2"));
        te_rmk2->setGeometry(QRect(680, 90, 211, 51));
        te_rmk2->setFont(font);
        le_symbol = new QLineEdit(CreateDlg);
        le_symbol->setObjectName(QString::fromUtf8("le_symbol"));
        le_symbol->setGeometry(QRect(220, 270, 239, 38));
        le_symbol->setFont(font);
        label_dir = new QLabel(CreateDlg);
        label_dir->setObjectName(QString::fromUtf8("label_dir"));
        label_dir->setGeometry(QRect(30, 10, 177, 51));
        label_dir->setFont(font);
        label_log = new QLabel(CreateDlg);
        label_log->setObjectName(QString::fromUtf8("label_log"));
        label_log->setGeometry(QRect(510, 160, 112, 59));
        label_log->setFont(font);
        pb_order = new QPushButton(CreateDlg);
        pb_order->setObjectName(QString::fromUtf8("pb_order"));
        pb_order->setGeometry(QRect(520, 340, 171, 41));
        pb_order->setFont(font);
        cb_exch = new QComboBox(CreateDlg);
        cb_exch->setObjectName(QString::fromUtf8("cb_exch"));
        cb_exch->setGeometry(QRect(220, 200, 239, 38));
        cb_exch->setFont(font);
        label_symbol = new QLabel(CreateDlg);
        label_symbol->setObjectName(QString::fromUtf8("label_symbol"));
        label_symbol->setGeometry(QRect(30, 270, 141, 31));
        label_symbol->setFont(font);
        cb_offset = new QComboBox(CreateDlg);
        cb_offset->setObjectName(QString::fromUtf8("cb_offset"));
        cb_offset->setGeometry(QRect(220, 80, 239, 38));
        cb_offset->setFont(font);
        le_qty = new QLineEdit(CreateDlg);
        le_qty->setObjectName(QString::fromUtf8("le_qty"));
        le_qty->setGeometry(QRect(220, 380, 239, 38));
        le_qty->setFont(font);
        pb_ctp = new QPushButton(CreateDlg);
        pb_ctp->setObjectName(QString::fromUtf8("pb_ctp"));
        pb_ctp->setGeometry(QRect(510, 230, 141, 41));

        retranslateUi(CreateDlg);

        QMetaObject::connectSlotsByName(CreateDlg);
    } // setupUi

    void retranslateUi(QDialog *CreateDlg)
    {
        CreateDlg->setWindowTitle(QApplication::translate("CreateDlg", "Dialog", nullptr));
        pb_reset->setText(QApplication::translate("CreateDlg", "Reset", nullptr));
        label_strg->setText(QApplication::translate("CreateDlg", "Strategy", nullptr));
        label_qty->setText(QApplication::translate("CreateDlg", "Qty", nullptr));
        label_offset->setText(QApplication::translate("CreateDlg", "Offset", nullptr));
        label_exch->setText(QApplication::translate("CreateDlg", "Exchange", nullptr));
        label_price->setText(QApplication::translate("CreateDlg", "Price", nullptr));
        label_rmk1->setText(QApplication::translate("CreateDlg", "Remark1", nullptr));
        label_rmk2->setText(QApplication::translate("CreateDlg", "Remark2", nullptr));
        label_dir->setText(QApplication::translate("CreateDlg", "Direction", nullptr));
        label_log->setText(QApplication::translate("CreateDlg", "Log Infor", nullptr));
        pb_order->setText(QApplication::translate("CreateDlg", "Order", nullptr));
        label_symbol->setText(QApplication::translate("CreateDlg", "Symbol", nullptr));
        pb_ctp->setText(QApplication::translate("CreateDlg", "Connect CTP", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateDlg: public Ui_CreateDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEDLG_H
