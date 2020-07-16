#include "sharparametr.h"
#include "ui_sharparametr.h"
#include "Engine.cpp"
SharParametr::SharParametr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SharParametr)
{
    ui->setupUi(this);
    this->setWindowTitle("Установка параметров шара");
}

SharParametr::~SharParametr()
{
    delete ui;
}

void SharParametr::on_ok_clicked()
{
    int rad = (ui->vys->text()).toInt();
    int det = (ui->color_3->currentIndex());
    double x = (ui->xx->text()).toDouble();
    double y = (ui->yy->text()).toDouble();
    double z = (ui->zz->text()).toDouble();
    int cl = (ui->color_2->currentIndex());  /// 0 это красный, 1 это зелёный, 2 это синий
    int tp = (ui->otbr->currentIndex()); /// 0 это точками, 1 это полигонами
    close();
    std::vector<std::vector<Point>> POINTS;
    std::vector<std::vector<Polygone>> POLYGONES;
    Point center(x,y,z);
     double ang=0;
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
     switch (det)
     {
     case 0:
         ang=9;
         break;
     case 1:
         ang=10;
         break;
     case 2:
         ang=15;
         break;
     case 3:
         ang=18;
         break;
     case 4:
         ang=24;
         break;
     case 5:
         ang=30;
         break;
     case 6:
         ang=36;
         break;
     case 7:
         ang=45;
         break;

     }

     Sphere thing(rad,ang,center,Figurecolor);
     POINTS.push_back(thing.getPOINTS());
     POLYGONES.push_back(thing.getTriangle());
     break;
     }
   }
     int figureNumber = 1;
     Engine (1280, 720, POINTS, POLYGONES, figureNumber);
}

