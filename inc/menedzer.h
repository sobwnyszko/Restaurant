#ifndef MENEDZER_H
#define MENEDZER_H

#include <QMainWindow>
#include "dodawanie_pracownikow.h"
#include "stoliki.h"
#include "potrawy.h"
#include "menu.h"

namespace Ui {
class Menedzer;
}

class Menedzer : public QMainWindow
{
    Q_OBJECT

public:
    explicit Menedzer(QWidget *parent = nullptr);
    ~Menedzer();
    void setID(int id){
        this->ID = id;
    }

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::Menedzer *ui;
    menu *Menu;
    Dodawanie_pracownikow *dod_prac;
    Stoliki *stolik;
    Potrawy *potrawy;
    int ID;
};

#endif // MENEDZER_H
