#ifndef MYFORM_H
#define MYFORM_H

#include <QDialog>

namespace Ui {
class myForm;
}

class myForm : public QDialog
{
    Q_OBJECT

public:
    explicit myForm(QWidget *parent = nullptr);
    ~myForm();
signals:
    void SendData(QString);
private slots:
    void on_pushButton_clicked();

private:
    Ui::myForm *ui;
};

#endif // MYFORM_H
