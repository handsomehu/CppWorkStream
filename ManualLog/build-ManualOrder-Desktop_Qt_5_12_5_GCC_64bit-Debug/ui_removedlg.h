/********************************************************************************
** Form generated from reading UI file 'removedlg.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REMOVEDLG_H
#define UI_REMOVEDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_RemoveDlg
{
public:
    QLabel *label_del;
    QPushButton *pb_del;
    QLineEdit *le_del;
    QLabel *label_infor;

    void setupUi(QDialog *RemoveDlg)
    {
        if (RemoveDlg->objectName().isEmpty())
            RemoveDlg->setObjectName(QString::fromUtf8("RemoveDlg"));
        RemoveDlg->resize(404, 271);
        label_del = new QLabel(RemoveDlg);
        label_del->setObjectName(QString::fromUtf8("label_del"));
        label_del->setGeometry(QRect(30, 20, 329, 41));
        QFont font;
        font.setPointSize(20);
        label_del->setFont(font);
        pb_del = new QPushButton(RemoveDlg);
        pb_del->setObjectName(QString::fromUtf8("pb_del"));
        pb_del->setGeometry(QRect(30, 150, 329, 38));
        pb_del->setFont(font);
        le_del = new QLineEdit(RemoveDlg);
        le_del->setObjectName(QString::fromUtf8("le_del"));
        le_del->setGeometry(QRect(30, 80, 329, 38));
        le_del->setFont(font);
        label_infor = new QLabel(RemoveDlg);
        label_infor->setObjectName(QString::fromUtf8("label_infor"));
        label_infor->setGeometry(QRect(40, 210, 311, 51));

        retranslateUi(RemoveDlg);

        QMetaObject::connectSlotsByName(RemoveDlg);
    } // setupUi

    void retranslateUi(QDialog *RemoveDlg)
    {
        RemoveDlg->setWindowTitle(QApplication::translate("RemoveDlg", "Dialog", nullptr));
        label_del->setText(QApplication::translate("RemoveDlg", "Delete Order ID", nullptr));
        pb_del->setText(QApplication::translate("RemoveDlg", "Delete", nullptr));
        label_infor->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class RemoveDlg: public Ui_RemoveDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REMOVEDLG_H
