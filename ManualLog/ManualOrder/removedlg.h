#ifndef REMOVEDLG_H
#define REMOVEDLG_H

#include <QDialog>
#include <QDebug>
#include <sqlhelper.h>

namespace Ui {
class RemoveDlg;
}

class RemoveDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RemoveDlg(QWidget *parent = nullptr);
    ~RemoveDlg();

private slots:
    void on_pb_del_clicked();

private:
    Ui::RemoveDlg *ui;
    SqlHelper dbhelper;
    //TradeWrapper trade;
    bool cnstatus;
};

#endif // REMOVEDLG_H
