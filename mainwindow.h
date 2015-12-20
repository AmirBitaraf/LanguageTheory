#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Bridge.h"
#include "addrule.h"


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

signals:
    void RulesChanged();
    
private slots:
    void on_actionImport_Rules_triggered();
    void on_rules_changes();
    void on_add_rule(QString lhs,QString rhs);
    void on_listWidget_currentRowChanged(int currentRow);

    void on_btnAddRule_clicked();

    void on_btnRemoveRule_clicked();

private:
    Ui::MainWindow *ui;
    QLabel * statusLabel;
    Language * language;
    AddRule * addRuleForm;
};

#endif // MAINWINDOW_H
