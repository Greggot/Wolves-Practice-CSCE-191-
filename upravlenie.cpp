#include "upravlenie.h"
#include "ui_upravlenie.h"

Upravlenie::Upravlenie(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Upravlenie)
{
    ui->setupUi(this);
    this->setWindowTitle("Ознакомление с управлением программы");
}

Upravlenie::~Upravlenie()
{
    delete ui;
}

void Upravlenie::on_pushButton_clicked()
{
    close();
}
