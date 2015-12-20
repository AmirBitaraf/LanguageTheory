#ifndef CYK_H
#define CYK_H

#include <QDialog>
#include <QTableWidget>

namespace Ui {
class CYK;
}

class CYK : public QDialog
{
    Q_OBJECT
    
public:
    explicit CYK(QWidget *parent = 0);
    ~CYK();
    QTableWidget * table;
    
private:
    Ui::CYK *ui;
};

#endif // CYK_H
