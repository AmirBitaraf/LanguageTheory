#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Bridge.h"


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

private:
    Ui::MainWindow *ui;
    QLabel * statusLabel;
    Language * language;
};

#endif // MAINWINDOW_H
