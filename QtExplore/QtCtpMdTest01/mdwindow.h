#ifndef MDWINDOW_H
#define MDWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MdWindow; }
QT_END_NAMESPACE

class MdWindow : public QMainWindow
{
    Q_OBJECT

public:
    MdWindow(QWidget *parent = nullptr);
    ~MdWindow();

private:
    Ui::MdWindow *ui;
};
#endif // MDWINDOW_H
