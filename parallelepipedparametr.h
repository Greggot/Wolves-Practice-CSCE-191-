#ifndef PARALLELEPIPEDPARAMETR_H
#define PARALLELEPIPEDPARAMETR_H

#include <QDialog>

namespace Ui {
class Parallelepipedparametr;
}

class Parallelepipedparametr : public QDialog
{
    Q_OBJECT

public:
    explicit Parallelepipedparametr(QWidget *parent = nullptr);
    ~Parallelepipedparametr();

private slots:
    void on_ok_clicked();

private:
    Ui::Parallelepipedparametr *ui;
};

#endif // PARALLELEPIPEDPARAMETR_H
