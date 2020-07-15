                                                                                                                                     #ifndef CUBPARAMETR_H
#define CUBPARAMETR_H

#include <QDialog>

namespace Ui {
class CubParametr;
}

class CubParametr : public QDialog
{
    Q_OBJECT

public:
    explicit CubParametr(QWidget *parent = nullptr);
    ~CubParametr();

private slots:
    void on_ok_clicked();

private:
    Ui::CubParametr *ui;
};

#endif // CUBPARAMETR_H
