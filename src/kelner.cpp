#include "kelner.h"
#include "ui_kelner.h"
#include <QSqlError>
#include <QMessageBox>
#include "databaseManager.h"

Kelner::Kelner(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Kelner)
{
    ui->setupUi(this);
    db = DatabaseManager::instance().getDatabase();
    if (db.open()){
        //qDebug() << "OK5!";
        model = new QSqlTableModel(this, db);
        model->setTable("potrawa_zamówienie");
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        if (!model->select()) {
            qDebug() << "Error selecting table:" << model->lastError().text();
            return;
        }

        ui->tableView->setModel(model);
        ui->tableView->resizeColumnsToContents();
        ui->tableView->setColumnWidth(3, 100);
    } else qDebug() << "Failed to connect to root mysql admin";

    Menu = new menu;
    StatusStolika = "Wolny";
    iloscObslugStolik = 0;
    this->setWindowTitle("Kelner");
}

Kelner::~Kelner()
{
    delete ui;
}

void Kelner::odnowianie()
{
    if (!model->select()) {
        qDebug() << "Error selecting table:" << model->lastError().text();
        return;
    }
}

void Kelner::on_pushButton_3_clicked()
{
    close();
}


void Kelner::on_spinBox_valueChanged(int arg1)
{
    NumerStolika = arg1;
}


void Kelner::on_comboBox_textActivated(const QString &arg1)
{
    StatusStolika = arg1;
}


void Kelner::on_pushButton_clicked()
{
    QSqlQuery q;
    q.prepare("call Aktualizuj_status_stolika (:NumerStolika, :Status, :inKelnerID, @poprawnosc , @nrZam)");

    q.bindValue(":NumerStolika", NumerStolika);
    q.bindValue(":Status", StatusStolika);
    q.bindValue(":inKelnerID", KelnerID);

    q.exec();
    q.exec("select @poprawnosc, @nrZam");
    if (q.next()) {
        if (q.value(0).toBool()){
            if (StatusStolika == "Wolny"){
                QMessageBox::about(this, "Aktualizacja statusu stolika", "Stolik został zwolniony");
                for (int i=0; i<NumeryStolikow.size(); i++){
                    if (NumeryStolikow[i] == NumerStolika){
                        NumeryStolikow.remove(i);
                        NumeryZamowienia.remove(i);
                    }
                }
            }
            if (StatusStolika == "Zajęty"){
                QMessageBox::about(this, "Aktualizacja statusu stolika", "Stolik został zajęty");
                NumeryStolikow.push_back(NumerStolika);
                NumeryZamowienia.push_back(q.value(1).toInt());
            }
            if (StatusStolika == "Zarezerwowany"){
                QMessageBox::about(this, "Aktualizacja statusu stolika", "Stolik został zajęty");
            }
        } else {
            if (StatusStolika == "Wolny"){
                QMessageBox::warning(this, "Błąd aktualizacji statusu stolika", "Dany stolik już jest wolny");
            }
            if (StatusStolika == "Zajęty"){
                QMessageBox::warning(this, "Błąd aktualizacji statusu stolika", "Dany stolik już jest zajęty");
            }
            if (StatusStolika == "Zarezerwowany"){
                QMessageBox::warning(this, "Błąd aktualizacji statusu stolika", "Dany stolik już jest zajęty");
            }
        }
    }
    ui->listWidget->clear();
    for (int i = 0; i < NumeryStolikow.size(); ++i) {
        ui->listWidget->addItem(QString::number(NumeryStolikow[i]));
    }
    ui->listWidget_2->clear();
    for (int i = 0; i < NumeryZamowienia.size(); ++i) {
        ui->listWidget_2->addItem(QString::number(NumeryZamowienia[i]));
    }
}





void Kelner::on_spinBox_2_valueChanged(int arg1)
{
    IDpotrawy = arg1;
}


void Kelner::on_spinBox_3_valueChanged(int arg1)
{
    NumerZamowienia = arg1;
}


void Kelner::on_pushButton_2_clicked()
{
    QSqlQuery q;
    q.prepare("call Dodawanie_zamowienia (:inIDPotrawy, :NrZam, @poprawnosc)");

    q.bindValue(":inIDPotrawy", IDpotrawy);
    q.bindValue(":NrZam", NumerZamowienia);

    q.exec();
    q.exec("select @poprawnosc");
    if (q.next()) {
        if (q.value(0).toBool()){
            QMessageBox::about(this, "Dodawanie zamówienia", "Zamówienie dodano poprawnie");
        }
    }
    odnowianie();
}


void Kelner::on_spinBox_4_valueChanged(int arg1)
{
    IDzamowienia = arg1;
}


void Kelner::on_pushButton_4_clicked()
{
    QSqlQuery q;
    q.prepare("call Usuwanie_zamowienia (:IDzamowienia, @poprawnosc)");

    q.bindValue(":IDzamowienia", IDzamowienia);

    q.exec();
    q.exec("select @poprawnosc");
    if (q.next()) {
        if (q.value(0).toBool()){
            QMessageBox::about(this, "Usuwanie zamówienia", "Zamówienie usuniento poprawnie");
        } else {
            QMessageBox::warning(this, "Błąd usuwania zamówienia", "Zamówienia pod danym ID nie istnieje");
        }
    }
    odnowianie();
}


void Kelner::on_pushButton_5_clicked()
{
    Menu -> show();
}

