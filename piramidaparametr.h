#ifndef PIRAMIDAPARAMETR_H
#define PIRAMIDAPARAMETR_H

#include <QDialog>

namespace Ui {
class PiramidaParametr;
}

class PiramidaParametr : public QDialog
{
    Q_OBJECT

public:
    explicit PiramidaParametr(QWidget *parent = nullptr);
    ~PiramidaParametr();

private slots:
    void on_ok_clicked();

    void on_ok_2_clicked();

private:
    Ui::PiramidaParametr *ui;
};

#endif // PIRAMIDAPARAMETR_H
