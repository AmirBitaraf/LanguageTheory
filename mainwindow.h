#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Bridge.h"
#include "addrule.h"
#include "cyk.h"
#include "est.h"


class QLabel;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString beautify(QString rule)
    {
        QString ret = "";
        for(int i = 0;i < rule.size();i++)
        {
            if(rule[i].isDigit()) ret += "<sub>"+rule[i]+"</sub>";
            else ret += QString(rule[i]);
        }
        return ret;
    }
signals:
    void RulesChanged();
    
private slots:
    void on_actionImport_Rules_triggered();
    void on_rules_changes();
    void on_add_rule(QString lhs,QString rhs);
    void on_listWidget_currentRowChanged(int currentRow);

    void on_btnAddRule_clicked();

    void on_btnRemoveRule_clicked();

    void on_btnProcess_clicked();

    void on_btnCNF_clicked();

    void on_btnCYK_clicked();

    void on_btnESP_clicked();

private:
    Ui::MainWindow *ui;
    QLabel * statusLabel;
    Language * language;
    AddRule * addRuleForm;
    CYK * cyk;
    EST * est;

};


#endif // MAINWINDOW_H
