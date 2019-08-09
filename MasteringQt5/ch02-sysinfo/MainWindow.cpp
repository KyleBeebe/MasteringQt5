
#include <QHBoxLayout>


#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mCpuWidget(this),
    mMemoryWidget(this)
{
    ui->setupUi(this);
    ui->centralWidget->setLayout(new QHBoxLayout());
    ui->centralWidget->layout()->addWidget(&mCpuWidget); //add cpu widget
    ui->centralWidget->layout()->addWidget(&mMemoryWidget); // add memory widget
}

MainWindow::~MainWindow()
{
    delete ui;
}
