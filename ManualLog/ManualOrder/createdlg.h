#ifndef CREATEDLG_H
#define CREATEDLG_H

#include <QDialog>
#include <QDate>
#include <QDateTime>
#include <QTime>
#include <QDebug>
#include <chrono>
#include <QTimer>
#include "sqlhelper.h"
#include "qmd.h"
#include "qtd.h"
#include "tdthread.h"
#include "mdthread.h"

namespace Ui {
class CreateDlg;
}

class CreateDlg : public QDialog
{
    Q_OBJECT

public:
    TdThread *tdthread;
    MdThread *mdthread;
    explicit CreateDlg(QWidget *parent = nullptr);
    ~CreateDlg();

signals:
    void LogOrder(QString insertsql);

    void uisendWT(QString);
public slots:
    void onTrade(QString insertsql);
    void querywork();
    void ReceiveWT(QString WTData);
    void ReceiveHQ(QString);
    void ReceiveAutoHQ(QString);
private slots:
    void on_pb_order_clicked();
    void on_pb_reset_clicked();
    void on_pb_ctp_clicked();

    void on_pb_db_clicked();

private:
    void ClearInput();
    void ConnActs();
    void ParseWT(CThostFtdcOrderField* pOrder);
    Ui::CreateDlg *ui;
    SqlHelper dbhelper;
    //QMd mktdata;
    bool cnstatus;
    QTimer *timer;
};

#endif // CREATEDLG_H
