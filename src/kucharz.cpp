#include "kucharz.h"
#include "ui_kucharz.h"
#include <QSqlError>
#include <QMessageBox>
#include "databaseManager.h"

Kucharz::Kucharz(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Kucharz)
{
    ui->setupUi(this);
    db = DatabaseManager::instance().getDatabase();
    if (db.open()){
        //qDebug() << "OK4!";
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
    this->setWindowTitle("Kucharz");
}

Kucharz::~Kucharz()
{
    delete ui;
}

void Kucharz::on_pushButton_3_clicked()
{
    close();
}

void Kucharz::odnowianie()
{
    if (!model->select()) {
        qDebug() << "Error selecting table:" << model->lastError().text();
        return;
    }
}


void Kucharz::on_spinBox_valueChanged(int arg1)
{
    IDzamowienia = arg1;
}


void Kucharz::on_comboBox_textActivated(const QString &arg1)
{
    status = arg1;
}


void Kucharz::on_pushButton_clicked()
{
    QSqlQuery q;
    q.prepare("call Aktualizacja_statusa (:IDzamowienia, :status, @poprawnosc)");
    q.bindValue(":IDzamowienia", IDzamowienia);
    q.bindValue(":status", status);
    q.exec();
    q.exec("select @poprawnosc");
    if (q.next()) {
        if (q.value(0).toBool()){
            QMessageBox::about(this, "Aktualizacja statusu", "Status został zaktualizowany");
        } else {
            QMessageBox::warning(this, "Błąd ID zamówienia", "Dane zamuwienie nie istnieje");
        }
    }
    odnowianie();
}


void Kucharz::on_pushButton_2_clicked()
{
    Menu -> show();
}

