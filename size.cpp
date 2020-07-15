#include "size.h"
#include "ui_size.h"

Size::Size(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Size)
{
    ui->setupUi(this);
}

Size::~Size()
{
    delete ui;
}

void Size::on_size_clicked()
{
    QString size = ui->size_2->text();

}
