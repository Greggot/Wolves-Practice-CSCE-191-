#ifndef SV_H
#define SV_H

#include <QDialog>

namespace Ui {
class SV;
}

class SV : public QDialog
{
    Q_OBJECT

public:
    explicit SV(QWidget *parent = nullptr);
    ~SV();

private:
    Ui::SV *ui;
};

#endif // SV_H
