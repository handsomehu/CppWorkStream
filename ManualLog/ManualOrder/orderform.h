#ifndef ORDERFORM_H
#define ORDERFORM_H

#include <QMainWindow>
#include <QDate>
#include <QDateTime>
#include <QTime>
#include "sqlhelper.h"

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
    void ClearInput();
    void on_pb_order_clicked();

    void on_pb_reset_clicked();

    void on_pb_del_clicked();

private:
    Ui::OrderForm *ui;
    SqlHelper dbhelper;

};
#endif // ORDERFORM_H
