#include "sekretarka.h"
#include "ui_sekretarka.h"
#include <QSqlError>
#include <QMessageBox>
#include "databaseManager.h"

Sekretarka::Sekretarka(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Sekretarka)
{
    ui->setupUi(this);
    db = DatabaseManager::instance().getDatabase();
    if (db.open()){
        //qDebug() << "OK8!";
        model = new QSqlTableModel(this, db);
        model->setTable("rezerwacja");
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        if (!model->select()) {
            qDebug() << "Error selecting table:" << model->lastError().text();
            return;
        }

        ui->tableView->setModel(model);
        ui->tableView->resizeColumnsToContents();
    } else qDebug() << "Failed to connect to root mysql admin";

    IDRezerwacji=5000;
    CoZmienic = "nic";
    data.setDate(2024, 7, 1);
    time.setHMS(0,0,0,0);
    NrStolika = 0;
    imie = "Anna";
    nazwisko = "NAZWISKO";
    NrKontaktowy = "NULL";

    this->setWindowTitle("Sekretarka");
}

Sekretarka::~Sekretarka()
{
    delete ui;
}

void Sekretarka::odnowianie()
{
    if (!model->select()) {
        qDebug() << "Error selecting table:" << model->lastError().text();
        return;
    }
}

void Sekretarka::on_pushButton_3_clicked()
{
    close();
}


void Sekretarka::on_dateEdit_userDateChanged(const QDate &date)
{
    data = date;
}


void Sekretarka::on_timeEdit_userTimeChanged(const QTime &time)
{
    this->time = time;
}


void Sekretarka::on_spinBox_valueChanged(int arg1)
{
    NrStolika = arg1;
}


void Sekretarka::on_lineEdit_editingFinished()
{
    imie = ui->lineEdit->text();
}


void Sekretarka::on_lineEdit_2_editingFinished()
{
    nazwisko = ui->lineEdit_2->text();
}


void Sekretarka::on_lineEdit_3_editingFinished()
{
    NrKontaktowy = ui->lineEdit_3->text();
}


void Sekretarka::on_spinBox_3_valueChanged(int arg1)
{
    IDRezerwacji = arg1;
}


void Sekretarka::on_comboBox_textActivated(const QString &arg1)
{
    CoZmienic = arg1;
}


void Sekretarka::on_dateEdit_2_userDateChanged(const QDate &date)
{
    data = date;
}


void Sekretarka::on_timeEdit_2_userTimeChanged(const QTime &time)
{
    this->time = time;
}


void Sekretarka::on_spinBox_2_valueChanged(int arg1)
{
    NrStolika = arg1;
}


void Sekretarka::on_lineEdit_5_editingFinished()
{
    imie = ui->lineEdit_5->text();
}


void Sekretarka::on_lineEdit_6_editingFinished()
{
    nazwisko = ui->lineEdit_6->text();
}


void Sekretarka::on_lineEdit_4_editingFinished()
{
    NrKontaktowy = ui->lineEdit_4->text();
}


void Sekretarka::on_spinBox_4_valueChanged(int arg1)
{
    IDRezerwacji = arg1;
}


void Sekretarka::on_pushButton_clicked()
{
    //Dodawanie
    QSqlQuery q;
    q.prepare("call Dodawanie_rezerwacji (:inData, :inGodzina, :inNrStolika, :inImie, :inNazwisko, :inNrKontakt, @poprawnosc)");
    q.bindValue(":inData", data);
    q.bindValue(":inGodzina", time);
    q.bindValue(":inNrStolika", NrStolika);
    q.bindValue(":inImie", imie);
    q.bindValue(":inNazwisko", nazwisko);
    q.bindValue(":inNrKontakt", NrKontaktowy);
    q.exec();
    q.exec("select @poprawnosc");
    if (q.next()) {
        if (q.value(0).toBool()){
            QMessageBox::about(this, "Dodawanie rezerwacji", "Rezerwacja dodana poprawnie");
        } else {
            QMessageBox::warning(this, "Błąd dodawania rezerwacji", "Dodanie rezerwacji niepowiodło");
        }
    }
    odnowianie();
}


void Sekretarka::on_pushButton_2_clicked()
{
    QSqlQuery q;
    q.prepare("call Modyfikacja_rezerwacji (:inIDRezerwacji, :CoZmienic, :inData, :inGodzina, :inNrStolika, :inImie, :inNazwisko, :inNrKontakt, @poprawnosc)");
    q.bindValue(":inIDRezerwacji", IDRezerwacji);
    q.bindValue(":CoZmienic", CoZmienic);
    q.bindValue(":inData", data);
    q.bindValue(":inGodzina", time);
    q.bindValue(":inNrStolika", NrStolika);
    q.bindValue(":inImie", imie);
    q.bindValue(":inNazwisko", nazwisko);
    q.bindValue(":inNrKontakt", NrKontaktowy);
    q.exec();
    q.exec("select @poprawnosc");
    if (q.next()) {
        if (q.value(0).toBool()){
            QMessageBox::about(this, "Modyfikowanie rezerwacji", "Rezerwacja została zmodyfikowana");
        } else {
            QMessageBox::warning(this, "Błąd modyfikowania rezerwacji", "Podane ID Rezerwacji nie istnieje");
        }
    }
    odnowianie();
}


void Sekretarka::on_pushButton_4_clicked()
{
    QSqlQuery q;
    q.prepare("call Usuwanie_rezerwacji (:inIDRezerwacji, @poprawnosc)");
    q.bindValue(":inIDRezerwacji", IDRezerwacji);
    q.exec();
    q.exec("select @poprawnosc");
    if (q.next()) {
        if (q.value(0).toBool()){
            QMessageBox::about(this, "Usuwanie rezerwacji", "Rezerwacja została usunięta");
        } else {
            QMessageBox::warning(this, "Błąd usuwania rezerwacji", "Podane ID Rezerwacji nie istnieje");
        }
    }
    odnowianie();
}

