#include "parallelepipedparametr.h"
#include "ui_parallelepipeparametr.h"
#include "Engine.cpp"

Parallelepipedparametr::Parallelepipedparametr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Parallelepipedparametr)
{
    ui->setupUi(this);
    this->setWindowTitle("Установка параметров параллелепипеда");
}

Parallelepipedparametr::~Parallelepipedparametr()
{
    delete ui;
}

void Parallelepipedparametr::on_ok_clicked()
{
    double  vys = (ui->vys->text()).toDouble();
    double  shir = (ui->shir->text()).toDouble();
    double  dl = (ui->dl->text()).toDouble();
    double x = (ui->xx->text()).toDouble();
    double y = (ui->yy->text()).toDouble();
    double z = (ui->zz->text()).toDouble();
    int cl = (ui->color->currentIndex());  /// 0 это красный, 1 это зелёный, 2 это синий
    int tp = (ui->otbr->currentIndex()); /// 0 это точками, 1 это полигонами
    close();
    std::vector<std::vector<Point>> POINTS;
    std::vector<std::vector<Polygone>> POLYGONES;
    Point center(x,y,z);
    switch(tp)
    {
    case 0:
    {
    sf::Color color(0,0,255,255);
    switch (cl)
    {
    case 0:
        color.r=255;
        color.g=0;
        color.b=0;
        break;
    case 1:
        color.r=0;
        color.g=255;
        color.b=0;
        break;
    case 2:
        color.r=0;
        color.g=0;
        color.b=255;
        break;
    }
   Parallelepiped thing(vys,shir,dl,center,color);
    POINTS.push_back(thing.getPOINTS());
    POLYGONES.push_back(thing.getTriangle());
        break;
    }
    case 1:
     sf::CircleShape shape (3.f);
     shape.setFillColor(sf::Color(69,228,255,255));
     shape.setOutlineThickness(2.f);
     shape.setOutlineColor(sf::Color(0,0,0,255));
     Parallelepiped thing(vys,shir,dl,center,shape);
     POINTS.push_back(thing.getPOINTS());
     POLYGONES.push_back(thing.getTriangle());
        break;
    }
    int figureNumber = 1;
    Engine (1280, 720, POINTS, POLYGONES, figureNumber);
}


void Parallelepipedparametr::on_ok_2_clicked()
{
    double  vys = (ui->vys->text()).toDouble();
    double  shir = (ui->shir->text()).toDouble();
    double  dl = (ui->dl->text()).toDouble();
    double x = (ui->xx->text()).toDouble();
    double y = (ui->yy->text()).toDouble();
    double z = (ui->zz->text()).toDouble();
        Point center(x,y,z);
         Parallelepiped thing(vys,shir,dl,center,sf::Color::Black);
        QString pl = QString::number(thing.getS());
        QString ob = QString::number(thing.getV());
        ui->pl->setText(pl);
        ui->ob->setText(ob);
}
