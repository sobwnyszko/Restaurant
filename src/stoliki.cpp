#include "stoliki.h"
#include "ui_stoliki.h"
#include <QSqlError>
#include <QMessageBox>
#include "databaseManager.h"

Stoliki::Stoliki(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Stoliki)
{
    ui->setupUi(this);
    db = DatabaseManager::instance().getDatabase();
    if (db.open()){
        //qDebug() << "OK2!";
        model = new QSqlTableModel(this, db);
        model->setTable("stolik");
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        if (!model->select()) {
            qDebug() << "Error selecting table:" << model->lastError().text();
            return;
        }

        ui->tableView->setModel(model);
        ui->tableView->resizeColumnsToContents();
    } else qDebug() << "Failed to connect to root mysql admin";

    this->setWindowTitle("Stoliki");
}

Stoliki::~Stoliki()
{
    delete ui;
}

void Stoliki::odnowianie()
{
    if (!model->select()) {
        qDebug() << "Error selecting table:" << model->lastError().text();
        return;
    }
}


void Stoliki::on_spinBox_valueChanged(int arg1)
{
    NumerStolika = arg1;
}


void Stoliki::on_spinBox_2_valueChanged(int arg1)
{
    iloscMejsc = arg1;
}


void Stoliki::on_pushButton_clicked()
{
    QSqlQuery q;
    q.prepare("call Dodawanie_stolikow (:numer, :ileMejsc, @poprawnosc)");
    q.bindValue(":numer", NumerStolika);
    q.bindValue(":ileMejsc", iloscMejsc);
    q.exec();
    q.exec("select @poprawnosc");
    if (q.next()) {
        if (q.value(0).toBool()){
            QMessageBox::about(this, "Dodawanie stolika", "Stolik dodan poprawnie");
        } else {
            QMessageBox::warning(this, "Błąd numera stolika", "Dany stolik już istnieje");
        }
    }
    odnowianie();
}


void Stoliki::on_spinBox_4_valueChanged(int arg1)
{
    NumerStolika = arg1;
}


void Stoliki::on_spinBox_3_valueChanged(int arg1)
{
    iloscMejsc = arg1;
}


void Stoliki::on_pushButton_2_clicked()
{
    QSqlQuery q;
    q.prepare("call Modyfikacja_stolikow (:numer, :ileMejsc, @poprawnosc)");
    q.bindValue(":numer", NumerStolika);
    q.bindValue(":ileMejsc", iloscMejsc);
    q.exec();
    q.exec("select @poprawnosc");
    if (q.next()) {
        if (q.value(0).toBool()){
            QMessageBox::about(this, "Modyfikacja stolika", "Stolik został zmodyfikowany");
        } else {
            QMessageBox::warning(this, "Błąd numera stolika", "Dany stolik nie istnieje");
        }
    }
    odnowianie();
}


void Stoliki::on_pushButton_3_clicked()
{
    close();
}


void Stoliki::on_spinBox_5_valueChanged(int arg1)
{
    NumerStolika = arg1;
}


void Stoliki::on_pushButton_5_clicked()
{
    QSqlQuery q;
    q.prepare("call Usuwanie_stolikow (:numer, @poprawnosc)");
    q.bindValue(":numer", NumerStolika);
    q.exec();
    q.exec("select @poprawnosc");
    if (q.next()) {
        if (q.value(0).toBool()){
            QMessageBox::about(this, "Usuwanie stolika", "Stolik został usunienty");
        } else {
            QMessageBox::warning(this, "Błąd numera stolika", "Dany stolik nie istnieje");
        }
    }
    odnowianie();
}

