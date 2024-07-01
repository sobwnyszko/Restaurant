#include "potrawy.h"
#include "ui_potrawy.h"
#include <QSqlError>
#include <QMessageBox>
#include "databaseManager.h"

Potrawy::Potrawy(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Potrawy)
{
    ui->setupUi(this);
    db = DatabaseManager::instance().getDatabase();
    if (db.open()){
        //qDebug() << "OK3!";
        modelPotrawy = new QSqlTableModel(this, db);
        modelPotrawy->setTable("potrawa");
        modelPotrawy->setEditStrategy(QSqlTableModel::OnManualSubmit);
        if (!modelPotrawy->select()) {
            qDebug() << "Error selecting table:" << modelPotrawy->lastError().text();
            return;
        }

        ui->tableView->setModel(modelPotrawy);
        ui->tableView->resizeColumnsToContents();

        modelDania = new QSqlTableModel(this, db);
        modelDania->setTable("danie");
        modelDania->setEditStrategy(QSqlTableModel::OnManualSubmit);
        if (!modelDania->select()) {
            qDebug() << "Error selecting table:" << modelPotrawy->lastError().text();
            return;
        }

        ui->tableView_2->setModel(modelDania);
        ui->tableView_2->resizeColumnsToContents();

    } else qDebug() << "Failed to connect to root mysql admin";

    this->setWindowTitle("Potrawy");
}

Potrawy::~Potrawy()
{
    delete ui;
}


void Potrawy::odnowianie()
{
    if (!modelPotrawy->select()) {
        qDebug() << "Error selecting table:" << modelPotrawy->lastError().text();
        return;
    }
}


void Potrawy::on_spinBox_valueChanged(int arg1)
{
    DanieID = arg1;
}


void Potrawy::on_lineEdit_editingFinished()
{
    Nazwa = ui->lineEdit->text();
}


void Potrawy::on_spinBox_2_valueChanged(int arg1)
{
    kalorii = arg1;
}


void Potrawy::on_doubleSpinBox_valueChanged(double arg1)
{
    waga = arg1;
}


void Potrawy::on_doubleSpinBox_2_valueChanged(double arg1)
{
    cena = arg1;
}


void Potrawy::on_spinBox_3_valueChanged(int arg1)
{
    PotrawaID = arg1;
}


void Potrawy::on_spinBox_4_valueChanged(int arg1)
{
    PotrawaID = arg1;
}


void Potrawy::on_spinBox_5_valueChanged(int arg1)
{
    kalorii = arg1;
}


void Potrawy::on_doubleSpinBox_3_valueChanged(double arg1)
{
    waga = arg1;
}


void Potrawy::on_doubleSpinBox_4_valueChanged(double arg1)
{
    cena = arg1;
}


void Potrawy::on_pushButton_4_clicked()
{
    close();
}


void Potrawy::on_pushButton_clicked()
{
    QSqlQuery q;
    q.prepare("call Dodawanie_potraw (:DanieID, :Nazwa, :Kalorii, :Waga, :Cena, @poprawnosc)");
    q.bindValue(":DanieID", DanieID);
    q.bindValue(":Nazwa", Nazwa);
    q.bindValue(":Kalorii", kalorii);
    q.bindValue(":Waga", waga);
    q.bindValue(":Cena", cena);
    q.exec();
    q.exec("select @poprawnosc");
    if (q.next()) {
        if (q.value(0).toBool()){
            QMessageBox::about(this, "Dodawanie potrawy", "Potrawa dodana poprawnie");
        } else {
            QMessageBox::warning(this, "Błąd nazwy potrawy", "Dana potrawa już istnieje");
        }
    }
    odnowianie();
}


void Potrawy::on_pushButton_3_clicked()
{
    QSqlQuery q;
    q.prepare("call Modyfikacja_potraw (:PotrawaID, :Kalorii, :Waga, :Cena, @poprawnosc)");
    q.bindValue(":PotrawaID", PotrawaID);
    q.bindValue(":Kalorii", kalorii);
    q.bindValue(":Waga", waga);
    q.bindValue(":Cena", cena);
    q.exec();
    q.exec("select @poprawnosc");
    if (q.next()) {
        if (q.value(0).toBool()){
            QMessageBox::about(this, "Modyfikacja potrawy", "Potrawa została zmodyfikowana");
        } else {
            QMessageBox::warning(this, "Błąd ID potrawy", "Dana potrawa nie istnieje");
        }
    }
    odnowianie();
}


void Potrawy::on_pushButton_2_clicked()
{
    QSqlQuery q;
    q.prepare("call Usuwanie_potraw (:PotrawaID, @poprawnosc)");
    q.bindValue(":PotrawaID", PotrawaID);
    q.exec();
    q.exec("select @poprawnosc");
    if (q.next()) {
        if (q.value(0).toBool()){
            QMessageBox::about(this, "Usuwanie potrawy", "Potrawa została usunienta");
        } else {
            QMessageBox::warning(this, "Błąd ID potrawy", "Dana potrawa nie istnieje");
        }
    }
    odnowianie();
}

