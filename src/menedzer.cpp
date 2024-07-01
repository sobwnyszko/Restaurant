#include "menedzer.h"
#include "ui_menedzer.h"

Menedzer::Menedzer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Menedzer)
{
    ui->setupUi(this);
    dod_prac = new Dodawanie_pracownikow();
    stolik = new Stoliki;
    potrawy = new Potrawy;
    Menu = new menu;
    this->setWindowTitle("Menedżer");
}

Menedzer::~Menedzer()
{
    delete ui;
}

void Menedzer::on_pushButton_3_clicked()
{
    close();
}


void Menedzer::on_pushButton_clicked()
{
    dod_prac->show();
}


void Menedzer::on_pushButton_2_clicked()
{
    stolik->show();
}


void Menedzer::on_pushButton_4_clicked()
{
    potrawy->show();
}


void Menedzer::on_pushButton_5_clicked()
{
    Menu -> show();
}

