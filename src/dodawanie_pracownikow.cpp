#include "dodawanie_pracownikow.h"
#include "ui_dodawanie_pracownikow.h"
#include <QMessageBox>
#include "databaseManager.h"

Dodawanie_pracownikow::Dodawanie_pracownikow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Dodawanie_pracownikow)
{
    ui->setupUi(this);
    db = DatabaseManager::instance().getDatabase();
    if (db.open()){
        //qDebug() << "OK1!";
    } else qDebug() << "Failed to connect to root mysql admin";


    this->setWindowTitle("Dodawanie pracowników");
}

Dodawanie_pracownikow::~Dodawanie_pracownikow()
{
    delete ui;
}

void Dodawanie_pracownikow::on_comboBox_textActivated(const QString &arg1)
{
    rola = arg1;
}


void Dodawanie_pracownikow::on_lineEdit_2_editingFinished()
{
    imie = ui->lineEdit_2->text();
}


void Dodawanie_pracownikow::on_lineEdit_3_editingFinished()
{
    nazwisko = ui->lineEdit_3->text();
}


void Dodawanie_pracownikow::on_lineEdit_4_editingFinished()
{
    PESEL = ui->lineEdit_4->text();
}


void Dodawanie_pracownikow::on_lineEdit_5_editingFinished()
{
    nrKotakt = ui->lineEdit_5->text();
}


void Dodawanie_pracownikow::on_lineEdit_6_editingFinished()
{
    mail = ui->lineEdit_6->text();
}


void Dodawanie_pracownikow::on_lineEdit_7_editingFinished()
{
    login = ui->lineEdit_7->text();
}


void Dodawanie_pracownikow::on_lineEdit_8_editingFinished()
{
    password = ui->lineEdit_8->text();
}


void Dodawanie_pracownikow::on_lineEdit_9_editingFinished()
{
    kodPocztowy = ui->lineEdit_9->text();
}


void Dodawanie_pracownikow::on_lineEdit_10_editingFinished()
{
    miasto = ui->lineEdit_10->text();
}


void Dodawanie_pracownikow::on_lineEdit_11_editingFinished()
{
    ulica = ui->lineEdit_11->text();
}


void Dodawanie_pracownikow::on_lineEdit_12_editingFinished()
{
    nrDomu = ui->lineEdit_12->text().toInt();
}


void Dodawanie_pracownikow::on_lineEdit_13_editingFinished()
{
    nrMieszkania = ui->lineEdit_13->text().toInt();
}


void Dodawanie_pracownikow::on_dateEdit_userDateChanged(const QDate &date)
{
    dataZatrudninia = date;
}


void Dodawanie_pracownikow::on_pushButton_clicked()
{
    QSqlQuery q;
    q.prepare("call Dodawanie_pracownikow (:rola, :imie, :nazwisko, :PESEL, :nrKont, :mail, :login, :password, "
              ":kodPoczt, :miasto, :ulica, :nrDomu, :nrMeszkania, :dataZatr, @status)");
    q.bindValue(":rola", rola);
    q.bindValue(":imie", imie);
    q.bindValue(":nazwisko", nazwisko);
    q.bindValue(":PESEL", PESEL);
    q.bindValue(":nrKont", nrKotakt);
    q.bindValue(":mail", mail);
    q.bindValue(":login", login);
    q.bindValue(":password", password);
    q.bindValue(":kodPoczt", kodPocztowy);
    q.bindValue(":miasto", miasto);
    q.bindValue(":ulica", ulica);
    q.bindValue(":nrDomu", nrDomu);
    q.bindValue(":nrMeszkania", nrMieszkania);
    q.bindValue(":dataZatr", dataZatrudninia);

    if (!q.exec()) {
        qDebug() << "błąd zapytania: ";
    }

    if (!q.exec("SELECT @status")) {
        qDebug() << "błąd otrzymania: ";
    }

    if (q.next()) {
        if (q.value(0).toBool()){
            QMessageBox::about(this, "Dodawanie pracownika", "Pracownik dodan poprawnie");
        } else {
            QMessageBox::warning(this, "Błąd dodawania pracownika",
                                 "Taki login już istnieje lub niepoprawnie wpisane dane");
        }
    }
}

void Dodawanie_pracownikow::on_pushButton_3_clicked()
{
    close();
}


void Dodawanie_pracownikow::on_comboBox_2_textActivated(const QString &arg1)
{
    rola = arg1;
    qDebug() << rola;
}


void Dodawanie_pracownikow::on_lineEdit_14_editingFinished()
{
    PESEL = ui->lineEdit_14->text();
    qDebug() << PESEL;
}


void Dodawanie_pracownikow::on_dateEdit_2_userDateChanged(const QDate &date)
{
    dataZwolnienia = date;
    qDebug() << date;
}


void Dodawanie_pracownikow::on_pushButton_2_clicked()
{
    QSqlQuery q;
    q.prepare("call Dezaktywacja_pracownikow (:rola, :PESEL, :dataZwol, @status)");
    q.bindValue(":rola", rola);
    q.bindValue(":PESEL", PESEL);
    q.bindValue(":dataZwol", dataZwolnienia);

    if (!q.exec()) {
        qDebug() << "błąd zapytania: ";
    }

    if (!q.exec("SELECT @status")) {
        qDebug() << "błąd otrzymania: ";
    }

    if (q.next()) {
        if (q.value(0).toBool()){
            QMessageBox::about(this, "Dezaktywacja pracownika", "Pracownik dezaktywowany poprawnie");
        } else {
            QMessageBox::warning(this, "Błąd dezaktywacji pracownika",
                                 "Niepoprawnie wpisane dane");
        }
    }
}

