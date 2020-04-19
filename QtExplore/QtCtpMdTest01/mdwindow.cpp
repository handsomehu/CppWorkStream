#include "mdwindow.h"
#include "ui_mdwindow.h"

MdWindow::MdWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MdWindow)
{
    ui->setupUi(this);
}

MdWindow::~MdWindow()
{
    delete ui;
}

