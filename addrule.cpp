#include "addrule.h"
#include "ui_addrule.h"
#include <QKeyEvent>
#include <QEvent>
#include <QDebug>

AddRule::AddRule(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRule)
{
    ui->setupUi(this);
    this->ui->textEdit->setTabChangesFocus(true);
    this->ui->textEdit_2->setTabChangesFocus(true);
    this->ui->textEdit_2->installEventFilter(this);
}


void AddRule::showEvent(QShowEvent * event)
{
    QDialog::showEvent(event);
    this->ui->textEdit_2->setText("");
    this->ui->textEdit->setText("");
    this->ui->textEdit->setFocus();
}

AddRule::~AddRule()
{
    delete ui;
}

QString process(QString str)
{
    QString ret = "";
    for(int i = 0;i < str.size();i++)
    {
        if(str[i].isDigit()) ret += "<sub>"+str[i]+"</sub>";
        else if(str[i]=='~') ret += "&lambda;";
        else ret += str[i];
    }
    return ret;
}

void AddRule::on_lineEdit_textEdited(const QString &str)
{

}

void AddRule::on_lineEdit_textChanged(const QString &str)
{

}

void AddRule::on_textEdit_textChanged()
{
    QString str = this->ui->textEdit->toPlainText();
    QTextCursor cr = ui->textEdit->textCursor();
    this->ui->textEdit->blockSignals(true);
    this->ui->textEdit->setHtml(process(str));
    this->ui->textEdit->blockSignals(false);
    ui->textEdit->setTextCursor(cr);
}

void AddRule::on_textEdit_2_textChanged()
{
    QString str = this->ui->textEdit_2->toPlainText();
    QTextCursor cr = ui->textEdit_2->textCursor();
    this->ui->textEdit_2->blockSignals(true);
    this->ui->textEdit_2->setHtml(process(str));
    this->ui->textEdit_2->blockSignals(false);
    ui->textEdit_2->setTextCursor(cr);
}

void AddRule::accept()
{
    QString lhs = ui->textEdit->toPlainText();
    QString rhs = ui->textEdit_2->toPlainText();
    for(int i = 0;i < lhs.size();i++) if(lhs[i]==955) lhs[i]='~';
    for(int i = 0;i < rhs.size();i++) if(rhs[i]==955) rhs[i]='~';
    emit RuleAdded(lhs,rhs);
}

bool AddRule::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Return)
        {
            this->accept();
            return true;
        }
    }
    return QObject::eventFilter(obj, event);
}


