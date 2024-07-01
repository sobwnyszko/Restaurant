#ifndef KELNER_H
#define KELNER_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include "menu.h"

namespace Ui {
class Kelner;
}

class Kelner : public QMainWindow
{
    Q_OBJECT

public:
    explicit Kelner(QWidget *parent = nullptr);
    ~Kelner();
    void setID(int id){
        this->ID = id;
    }
    void setKelnerID(int KelnerId){
        this->KelnerID = KelnerId;
    }
    void odnowianie();

private slots:
    void on_pushButton_3_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_comboBox_textActivated(const QString &arg1);

    void on_pushButton_clicked();

    void on_spinBox_2_valueChanged(int arg1);

    void on_spinBox_3_valueChanged(int arg1);

    void on_pushButton_2_clicked();

    void on_spinBox_4_valueChanged(int arg1);

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::Kelner *ui;
    menu *Menu;
    int ID;
    QSqlDatabase db;
    QSqlTableModel *model;
    QVector <int> NumeryStolikow;
    int NumerStolika;
    int KelnerID;
    QString StatusStolika;
    QVector <int> NumeryZamowienia;
    int iloscObslugStolik;
    int IDpotrawy;
    int NumerZamowienia;
    int IDzamowienia;
};

#endif // KELNER_H
