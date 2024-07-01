#include "menu.h"
#include "ui_menu.h"
#include <QSqlError>
#include "databaseManager.h"

menu::menu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::menu)
{
    ui->setupUi(this);
    db = DatabaseManager::instance().getDatabase();
    if (db.open()){
        //qDebug() << "OK7!";
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

    this->setWindowTitle("Menu");
}

menu::~menu()
{
    delete ui;
}

void menu::odnowianie()
{
    if (!modelPotrawy->select()) {
        qDebug() << "Error selecting table:" << modelPotrawy->lastError().text();
        return;
    }
}

void menu::on_pushButton_clicked()
{

}


void menu::on_pushButton_2_clicked()
{
    close();
}

