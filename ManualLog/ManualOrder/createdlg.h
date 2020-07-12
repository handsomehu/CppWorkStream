#ifndef CREATEDLG_H
#define CREATEDLG_H

#include <QMessageBox>
#include <QMenu>
#include <QAction>
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
#include <QContextMenuEvent>
#include <limits>

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
    void uisendCJ(QString);
public slots:
    void onTrade(QString insertsql);
    void querywork();
    void ReceiveWT(QString WTData);
    void ReceiveHQ(QString);
    void ReceiveCJ(QString);
    void ReceiveAutoHQ(QString);
    void cancelorder();
    void contextMenuEvent(QContextMenuEvent *event);
private slots:
    void on_pb_order_clicked();
    void on_pb_reset_clicked();
    void on_pb_ctp_clicked();
    //void on_Wt_MenuReq(QPoint pos);
    void on_pb_db_clicked();

    void on_WtTable_customContextMenuRequested(const QPoint &pos);

private:
    void ClearInput();
    void ConnActs();
    void ParseWT(std::shared_ptr<CThostFtdcOrderField> pOrder);
    void ParseCJ(std::shared_ptr<CThostFtdcTradeField> pTrade);
    Ui::CreateDlg *ui;
    SqlHelper dbhelper;
    //QMd mktdata;
    bool cnstatus;
    QTimer *timer;
    QMenu *cancel_menu;
    QAction *qact;
    void actions();
};

#endif // CREATEDLG_H
