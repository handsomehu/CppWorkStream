#ifndef ORDERFORM_H
#define ORDERFORM_H

#include <QMainWindow>
#include <QDialog>
#include <QDate>
#include <QDateTime>
#include <QTime>
#include "sqlhelper.h"
#include "tradewrapper.h"
#include "createdlg.h"
#include "removedlg.h"

QT_BEGIN_NAMESPACE
namespace Ui { class OrderForm; }
QT_END_NAMESPACE

class OrderForm : public QMainWindow
{
    Q_OBJECT

public:
    OrderForm(QWidget *parent = nullptr);
    ~OrderForm();

private slots:

    void on_actionCreate_triggered();

    void on_actionRemove_triggered();

private:
    Ui::OrderForm *ui;

};
#endif // ORDERFORM_H
