#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->statusLabel = new QLabel("Language Theory :)");
    statusBar()->addWidget(this->statusLabel);
}

MainWindow::~MainWindow()
{
    delete ui;
}
