#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databaseManager.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = DatabaseManager::instance().getDatabase();
    if (db.open()){
        //qDebug() << "OK0!";
    } else qDebug() << "Failed to connect to root mysql admin";

    kelner = new Kelner();
    kucharz = new Kucharz();
    menedzer = new Menedzer();
    sekretarka = new Sekretarka();

    this->setWindowTitle("Logowanie");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    close();
}


void MainWindow::on_pushButton_clicked()
{
    bool poprawnosc = 0;
    int id;
    QSqlQuery q;
    q.prepare("call Logowanie (:login, :password, @poprawnosc, @id)");
    q.bindValue(":login", login);
    q.bindValue(":password", password);
    q.exec();
    q.exec("select @poprawnosc, @id");
    if (q.next()) {
        poprawnosc = q.value(0).toBool();
        id = q.value(1).toInt();
    }

    if (poprawnosc == false){
        QMessageBox::warning(this, "Błąd logowania", "Niepoprawny login lub hasło");
    }

    if (login[0] == '3' && poprawnosc == true){

        QSqlQuery q;
        q.prepare("call getKelnerID (:PracownikID, @KelnerID)");
        q.bindValue(":PracownikID", id);
        q.exec();
        q.exec("select @KelnerID");
        if (q.next()) {
            kelner->setKelnerID(q.value(0).toInt());
        }
        kelner -> setID(id);
        kelner -> setWindowTitle("Kelner");
        kelner -> show();
    }

    if (login[0] == '4' && poprawnosc == true){
        kucharz -> setID(id);
        kucharz -> setWindowTitle("Kucharz");
        kucharz -> show();
    }

    if (login[0] == '1' && poprawnosc == true){
        menedzer->setID(id);
        menedzer -> setWindowTitle("Menedzer");
        menedzer -> show();
    }

    if (login[0] == '2' && poprawnosc == true){
        sekretarka -> setID(id);
        sekretarka -> setWindowTitle("Sekretarka");
        sekretarka -> show();
    }
}


void MainWindow::on_lineEdit_editingFinished()
{
    login = ui->lineEdit->text();
}


void MainWindow::on_lineEdit_2_editingFinished()
{
    password = ui->lineEdit_2->text();
}

