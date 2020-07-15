#ifndef CILINDRPARAMTR_H
#define CILINDRPARAMTR_H

#include <QDialog>

namespace Ui {
class CilindrParamtr;
}

class CilindrParamtr : public QDialog
{
    Q_OBJECT

public:
    explicit CilindrParamtr(QWidget *parent = nullptr);
    ~CilindrParamtr();

private slots:
    void on_ok_clicked();

private:
    Ui::CilindrParamtr *ui;
};

#endif // CILINDRPARAMTR_H
