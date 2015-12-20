#include "cyk.h"
#include "ui_cyk.h"

CYK::CYK(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CYK)
{
    ui->setupUi(this);
    this->table = this->ui->tableWidget;
}

CYK::~CYK()
{
    delete ui;
}
