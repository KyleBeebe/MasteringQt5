
#include <QHBoxLayout>


#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mCpuWidget(this)
{
    ui->setupUi(this);
    ui->centralWidget->setLayout(new QHBoxLayout());
    ui->centralWidget->layout()->addWidget(&mCpuWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
