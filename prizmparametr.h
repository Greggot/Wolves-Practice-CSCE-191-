#ifndef PRIZMPARAMETR_H
#define PRIZMPARAMETR_H

#include <QDialog>

namespace Ui {
class PrizmParametr;
}

class PrizmParametr : public QDialog
{
    Q_OBJECT

public:
    explicit PrizmParametr(QWidget *parent = nullptr);
    ~PrizmParametr();

private slots:
    void on_ok_clicked();

private:
    Ui::PrizmParametr *ui;
};

#endif // PRIZMPARAMETR_H
