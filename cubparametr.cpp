#include "cubparametr.h"
#include "ui_cubparametr.h"
#include "Engine.cpp"

CubParametr::CubParametr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CubParametr)
{
    ui->setupUi(this);
    this->setWindowTitle("Установка параметров куба");

}

CubParametr::~CubParametr()
{
    delete ui;
}

void CubParametr::on_ok_clicked()
{
    double rebro = (ui->rebro->text()).toDouble();
    double x = (ui->rebro_2->text()).toDouble();
    double y = (ui->rebro_3->text()).toDouble();
    double z = (ui->rebro_4->text()).toDouble();
    int cl = (ui->color->currentIndex());  /// 0 это красный, 1 это зелёный, 2 это синий
    int tp = (ui->comboBox_2->currentIndex()); /// 0 это точками, 1 это полигонами
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
    Cube thing(rebro, center, color);
    POINTS.push_back(thing.getPOINTS());
    POLYGONES.push_back(thing.getTriangle());
        break;
    }
    case 1:
     sf::CircleShape shape (3.f);
     shape.setFillColor(sf::Color(69,228,255,255));
     shape.setOutlineThickness(2.f);
     shape.setOutlineColor(sf::Color(0,0,0,255));
     Cube thing(rebro, center, shape);
     POINTS.push_back(thing.getPOINTS());
     POLYGONES.push_back(thing.getTriangle());
        break;
    }
    int figureNumber = 1;
    Engine (1280, 720, POINTS, POLYGONES, figureNumber);
}
