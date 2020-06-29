#ifndef CREATEDLG_H
#define CREATEDLG_H

#include <QDialog>
#include <QDate>
#include <QDateTime>
#include <QTime>
#include <QDebug>
#include <chrono>
#include "sqlhelper.h"
#include "tradewrapper.h"

namespace Ui {
class CreateDlg;
}

class CreateDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CreateDlg(QWidget *parent = nullptr);
    ~CreateDlg();

signals:
    void LogOrder(QString insertsql);
public slots:
    void onTrade(QString insertsql);
private slots:
    void on_pb_order_clicked();
    void on_pb_reset_clicked();
    void on_pb_ctp_clicked();
private:
    void ClearInput();
    void ConnActs();
    Ui::CreateDlg *ui;
    SqlHelper dbhelper;
    TradeWrapper trade;
    bool cnstatus;
};

#endif // CREATEDLG_H
