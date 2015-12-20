#include "est.h"
#include "ui_est.h"

EST::EST(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EST)
{
    ui->setupUi(this);
    this->tree = ui->treeView;
}

EST::~EST()
{
    delete ui;
}
