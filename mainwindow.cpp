#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this,SIGNAL(RulesChanged()),this,SLOT(on_rules_changes()));
    this->statusLabel = new QLabel("Language Theory :)");
    statusBar()->addWidget(this->statusLabel);
    this->language = new Language();
    emit RulesChanged();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_rules_changes()
{
    ui->btnProcess->setEnabled(false);
    ui->btnCYK->setEnabled(false);
    ui->btnCNF->setEnabled(false);
    ui->btnGNF->setEnabled(false);
    ui->btnESP->setEnabled(false);
    if(this->language->rules.size())
    {
        ui->btnProcess->setEnabled(true);
        this->ui->listWidget->clear();
        for(int i = 0;i < language->rules.size();i++)
        {
            QLabel * label = new QLabel(language->rules[i].getFormatted());
            QListWidgetItem * item = new QListWidgetItem();
            //item->setTextAlignment(Qt::AlignHCenter);
            //label->setAlignment(Qt::AlignHCenter);
            this->ui->listWidget->addItem(item);
            this->ui->listWidget->setItemWidget(item,label);
        }
    }
}

void MainWindow::on_actionImport_Rules_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open Rules...",QString(),"Text Files(*.txt *.in *.rules)");
    ifstream fin(filename.toStdString().c_str());
    try
    {
        language->loadRules(fin);
    }
    catch(RuleException & e)
    {
        language->clearRules();
        QMessageBox::critical(this,"Error",e.what());
    }

    emit RulesChanged();
}

void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    if(currentRow >= 0)
    {
       this->ui->btnRemoveRule->setEnabled(true);
    }
    else
    {
        this->ui->btnRemoveRule->setEnabled(false);
    }
}
