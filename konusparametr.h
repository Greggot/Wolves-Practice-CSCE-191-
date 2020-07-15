#ifndef KONUSPARAMETR_H
#define KONUSPARAMETR_H

#include <QDialog>

namespace Ui {
class KonusParametr;
}

class KonusParametr : public QDialog
{
    Q_OBJECT

public:
    explicit KonusParametr(QWidget *parent = nullptr);
    ~KonusParametr();

private slots:
    void on_ok_2_clicked();

private:
    Ui::KonusParametr *ui;
};

#endif // KONUSPARAMETR_H
