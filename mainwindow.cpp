#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "size.h"
#include "prizmparametr.h"
#include "konusparametr.h"
#include "cilindrparametr.h"
#include "sharparametr.h"
#include "piramidaparametr.h"
#include "cubparametr.h"
#include "parallelepipedparametr.h"
#include "upravlenie.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)


{
    ui->setupUi(this);
    QPixmap pix(":/img/Images/cub2.png");
    int w = ui->img1->width();
    int h = ui->img1->height();
    ui->img1->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

    QPixmap pix1(":/img/Images/prizma.png");
    int w1 = ui->img1_2->width();
    int h1 = ui->img1_2->height();
    ui->img1_2->setPixmap(pix1.scaled(w1,h1,Qt::KeepAspectRatio));

    QPixmap pix2(":/img/Images/cilindr.png");
    int w2 = ui->img1_3->width();
    int h2 = ui->img1_3->height();
    ui->img1_3->setPixmap(pix2.scaled(w2,h2,Qt::KeepAspectRatio));

    QPixmap pix3(":/img/Images/piramida.png");
    int w3 = ui->img1_4->width();
    int h3 = ui->img1_4->height();
    ui->img1_4->setPixmap(pix3.scaled(w3,h3,Qt::KeepAspectRatio));

    QPixmap pix4(":/img/Images/shar.png");
    int w4 = ui->img1_5->width();
    int h4 = ui->img1_5->height();
    ui->img1_5->setPixmap(pix4.scaled(w4,h4,Qt::KeepAspectRatio));

    QPixmap pix5(":/img/Images/konus2.png");
    int w5 = ui->img1_6->width();
    int h5 = ui->img1_6->height();
    ui->img1_6->setPixmap(pix5.scaled(w5,h5,Qt::KeepAspectRatio));

    QPixmap pix6(":/img/Images/parall.png");
    int w6 = ui->img1_7->width();
    int h6 = ui->img1_7->height();
    ui->img1_7->setPixmap(pix6.scaled(w6,h6,Qt::KeepAspectRatio));

    QPixmap pix7(":/img/Images/Без имени-1.jpg");
    int w7 = ui->label_2->width();
    int h7 = ui->label_2->height();
    ui->label_2->setPixmap(pix7.scaled(w7,h7,Qt::KeepAspectRatio));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Cub_clicked()
{
    CubParametr window;
    window.setModal(true);
    window.exec();
}

void MainWindow::on_Prizma_clicked()
{
    PrizmParametr window;
    window.setModal(true);
    window.exec();
}

void MainWindow::on_Konus_clicked()
{
    KonusParametr window;
    window.setModal(true);
    window.exec();
}

void MainWindow::on_Cilindr_clicked()
{
    CilindrParamtr window;
    window.setModal(true);
    window.exec();
}

void MainWindow::on_Shar_clicked()
{
    SharParametr window;
    window.setModal(true);
    window.exec();
}

void MainWindow::on_Piramida_clicked()
{
    PiramidaParametr window;
    window.setModal(true);
    window.exec();
}

void MainWindow::on_Konus_2_clicked()
{
    Parallelepipedparametr window;
    window.setModal(true);
    window.exec();
}

void MainWindow::on_pushButton_clicked()
{
    Upravlenie window;
    window.setModal(true);
    window.exec();
}
