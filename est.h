#ifndef EST_H
#define EST_H

#include <QDialog>
#include <QTreeView>

namespace Ui {
class EST;
}

class EST : public QDialog
{
    Q_OBJECT
    
public:
    explicit EST(QWidget *parent = 0);
    ~EST();
    QTreeView * tree;
    
private:
    Ui::EST *ui;
};

#endif // EST_H
