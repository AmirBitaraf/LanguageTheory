#include "mainwindow.h"
#include "ui_mainwindow.h"
#if defined(Q_WS_WIN)
#include <windows.h>
#endif


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->addRuleForm = new AddRule();
    connect(this,SIGNAL(RulesChanged()),this,SLOT(on_rules_changes()));
    connect(this->addRuleForm,SIGNAL(RuleAdded(QString,QString)),this,SLOT(on_add_rule(QString,QString)));
    this->statusLabel = new QLabel("Language Theory :)");
    statusBar()->addWidget(this->statusLabel);
    this->language = new Language();
    emit RulesChanged();
    this->ui->btnRemoveRule->setEnabled(false);
    this->cyk = new CYK();
    this->est = new EST();
    QShortcut *shortcut = new QShortcut(QKeySequence("Ctrl+I"), this);
    QObject::connect(shortcut, SIGNAL(activated()), this->ui->btnAddRule, SLOT(click()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_rules_changes()
{
    this->ui->listWidget->clear();
    ui->btnProcess->setEnabled(false);
    ui->btnCYK->setEnabled(false);
    ui->btnCNF->setEnabled(false);
    ui->btnGNF->setEnabled(false);
    ui->btnESP->setEnabled(false);
    if(this->language->rules.size())
    {
        ui->btnProcess->setEnabled(true);
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

void MainWindow::on_add_rule(QString lhs, QString rhs)
{
    this->addRuleForm->close();
    try
    {
        this->language->addRule(Rule(lhs.toStdString(),rhs.toStdString()));
        emit RulesChanged();
    }
    catch(RuleException & e)
    {
        QMessageBox::critical(this,"Error",e.what());
    }
}

void MainWindow::on_btnAddRule_clicked()
{
    //this->addRuleForm->setWindowFlags(Qt::WindowCloseButtonHint);
    #if defined(Q_WS_WIN)

        HWND hwnd = this->addRuleForm->winId();
        LONG_PTR style = GetWindowLongPtr(hwnd, GWL_STYLE);
        style &= ~WS_SYSMENU;
        SetWindowLongPtr(hwnd, GWL_STYLE, style);
        SetWindowPos(hwnd, 0, 0, 0, 0, 0,
            SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
    #endif
    this->addRuleForm->showNormal();
}

void MainWindow::on_btnRemoveRule_clicked()
{
    if(!this->ui->listWidget->selectedItems().size()) return;
    int select = this->ui->listWidget->row(this->ui->listWidget->selectedItems()[0]);
    this->language->removeRule(select);
    emit RulesChanged();
}

void MainWindow::on_btnProcess_clicked()
{
    this->language->processLanguage();
    emit RulesChanged();
    this->ui->btnCNF->setEnabled(true);
    this->ui->btnESP->setEnabled(true);
    this->ui->btnGNF->setEnabled(true);
}

void MainWindow::on_btnCNF_clicked()
{
    this->language->convertCNF();
    emit RulesChanged();
    this->ui->btnCNF->setEnabled(true);
    this->ui->btnESP->setEnabled(true);
    this->ui->btnGNF->setEnabled(true);
    this->ui->btnCYK->setEnabled(true);
}

void MainWindow::on_btnCYK_clicked()
{
    cyk->table->clear();
    this->cyk->setWindowFlags(Qt::WindowCloseButtonHint);
    QString eval = this->ui->txtString->text();

    if(eval.size()==0)
    {
        QMessageBox::warning(this,"String","Please Enter String to Evaluate");
        return;
    }

    this->language->performCYK(eval.toStdString());

    QStringList labels;
    cyk->table->setRowCount(eval.size());
    for(int i = 0;i < eval.size();i++){
        cyk->table->insertColumn(i);
        labels << QString::number(i);
    }
    cyk->table->setHorizontalHeaderLabels(labels);
    cyk->table->setVerticalHeaderLabels(labels);
    cyk->table->verticalHeader()->setVisible(false);
    cyk->table->horizontalHeader()->setVisible(false);

    for(int i = 0;i < eval.size();i++)
    {
        for(int j = 0; j < eval.size();j++)
        {
            QLabel * label = new QLabel("");
            QTableWidgetItem * item = new QTableWidgetItem();
            label->setStyleSheet("QLabel {background-color: #AAA;};");
            cyk->table->setItem(i,j,item);
            cyk->table->setCellWidget(i,j,label);

        }
    }

    for(int i = 1;i <= eval.size();i++)
    {
        for(int j = 1; i+j <= eval.size()+1;j++)
        {
            QString lbl = "<div style='float:left'><sup>";
            lbl += QString::number(j)+QString::number(i+j-1);
            lbl += "</sup></div><div align='center'>";

            lbl += "{";
            bool flag = false;
            for(int k = 0;k < this->language->IND.size();k++)
            {
                if(this->language->P[i][j][k])
                {
                    if(flag) lbl += ", ";
                    flag = true;
                    lbl += QString(this->language->IND[k].c_str());
                }
            }
            lbl += "}";
            lbl += "</div>";
            QLabel * label = new QLabel(beautify(lbl));
            QTableWidgetItem * item = new QTableWidgetItem();
            cyk->table->setItem(i-1,j-1,item);
            cyk->table->setCellWidget(i-1,j-1,label);
        }
    }



    this->cyk->showNormal();
}

void MainWindow::on_btnESP_clicked()
{
    this->est->setWindowFlags(Qt::WindowCloseButtonHint);
    QString eval = this->ui->txtString->text();
    QStandardItemModel * model = new QStandardItemModel(1,1);

    if(eval.size()==0)
    {
        QMessageBox::warning(this,"String","Please Enter String to Evaluate");
        return;
    }
    this->language->tree = this->est->tree;
    this->language->performESP(eval.toStdString(),model);

    if(language->flag)
    {
        QMessageBox::information(this,"Found","String Parsed in Language!");
    }

    this->est->tree->header()->hide();

    this->est->tree->setModel(model);

    this->est->show();
}
