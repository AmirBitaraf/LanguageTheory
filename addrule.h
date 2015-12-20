#ifndef ADDRULE_H
#define ADDRULE_H

#include <QDialog>

namespace Ui {
class AddRule;
}

class AddRule : public QDialog
{
    Q_OBJECT
    
public:
    explicit AddRule(QWidget *parent = 0);
    ~AddRule();
protected:
    bool eventFilter(QObject *obj, QEvent *event);
signals:
    void RuleAdded(QString lhs, QString rhs);
private slots:
    void on_lineEdit_textChanged(const QString &arg1);
    void showEvent(QShowEvent *);
    void on_lineEdit_textEdited(const QString &arg1);
    void on_textEdit_textChanged();
    void on_textEdit_2_textChanged();
    void accept();

private:
    Ui::AddRule *ui;
};

#endif // ADDRULE_H
