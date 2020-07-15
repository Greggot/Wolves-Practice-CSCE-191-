#ifndef UPRAVLENIE_H
#define UPRAVLENIE_H

#include <QDialog>

namespace Ui {
class Upravlenie;
}

class Upravlenie : public QDialog
{
    Q_OBJECT

public:
    explicit Upravlenie(QWidget *parent = nullptr);
    ~Upravlenie();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Upravlenie *ui;
};

#endif // UPRAVLENIE_H
