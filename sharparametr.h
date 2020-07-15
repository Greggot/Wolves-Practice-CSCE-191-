#ifndef SHARPARAMETR_H
#define SHARPARAMETR_H

#include <QDialog>

namespace Ui {
class SharParametr;
}

class SharParametr : public QDialog
{
    Q_OBJECT

public:
    explicit SharParametr(QWidget *parent = nullptr);
    ~SharParametr();

private slots:
    void on_ok_clicked();

private:
    Ui::SharParametr *ui;
};

#endif // SHARPARAMETR_H
