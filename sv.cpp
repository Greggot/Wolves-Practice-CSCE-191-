#include "sv.h"
#include "ui_sv.h"
#include "cubparametr.cpp"

SV::SV(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SV)
{
    ui->setupUi(this);
}

SV::~SV()
{
    delete ui;
}
