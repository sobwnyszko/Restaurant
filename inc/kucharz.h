#ifndef KUCHARZ_H
#define KUCHARZ_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include "menu.h"

namespace Ui {
class Kucharz;
}

class Kucharz : public QMainWindow
{
    Q_OBJECT

public:
    explicit Kucharz(QWidget *parent = nullptr);
    ~Kucharz();
    void setID(int id){
        this->ID = id;
    }
    void odnowianie();

private slots:
    void on_pushButton_3_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_comboBox_textActivated(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Kucharz *ui;
    menu *Menu;
    int ID;
    QSqlDatabase db;
    QSqlTableModel *model;
    int IDzamowienia;
    QString status;
};

#endif // KUCHARZ_H
