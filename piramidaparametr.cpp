#include "piramidaparametr.h"
#include "ui_piramidaparametr.h"
#include "Engine.cpp"

PiramidaParametr::PiramidaParametr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PiramidaParametr)
{
    ui->setupUi(this);
    this->setWindowTitle("Установка параметров пирамиды");
}

PiramidaParametr::~PiramidaParametr()
{
    delete ui;
}

void PiramidaParametr::on_ok_clicked()
{
    int vys = (ui->vys->text()).toInt();
    int diag = (ui->dm->text()).toInt();
    int tch = (ui->rebro_5->text()).toInt();
    double x = (ui->xx->text()).toDouble();
    double y = (ui->yy->text()).toDouble();
    double z = (ui->zz->text()).toDouble();
    int cl = (ui->color_2->currentIndex());  /// 0 это красный, 1 это зелёный, 2 это синий
    int tp = (ui->otbr->currentIndex()); /// 0 это точками, 1 это полигонами
    close();
    std::vector<std::vector<Point>> POINTS;
    std::vector<std::vector<Polygone>> POLYGONES;
    Point center(x,y,z);
     Point cent(0,0,0);

     switch (tp)
     {
     case 0:
     {
   sf::Color Figurecolor(0,0,255,255);
     switch (cl)
     {
     case 0:
         Figurecolor.r=255;
         Figurecolor.g=0;
         Figurecolor.b=0;
         break;
     case 1:
         Figurecolor.r=0;
         Figurecolor.g=255;
         Figurecolor.b=0;
         break;
     case 2:
         Figurecolor.r=0;
         Figurecolor.g=0;
         Figurecolor.b=255;
         break;
     }
     Pyramid_Cone thing(vys, diag, tch+1, cent, Figurecolor);
     POINTS.push_back(thing.getPOINTS());
     POLYGONES.push_back(thing.getTriangle());
     break;
     }
     case 1:
     {
         sf::CircleShape shape (3.f);
         shape.setFillColor(sf::Color(69,228,255,255));
         shape.setOutlineThickness(2.f);
         shape.setOutlineColor(sf::Color(0,0,0,255));
         Pyramid_Cone thing(vys,diag,tch+1,cent, shape);
         POINTS.push_back(thing.getPOINTS());
         POLYGONES.push_back(thing.getTriangle());
            break;
     }
     }
     int figureNumber = 1;
     Engine (1280, 720, POINTS, POLYGONES, figureNumber);
   }

