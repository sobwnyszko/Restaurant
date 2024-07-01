#ifndef STOLIKI_H
#define STOLIKI_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>

namespace Ui {
class Stoliki;
}

class Stoliki : public QMainWindow
{
    Q_OBJECT

public:
    explicit Stoliki(QWidget *parent = nullptr);
    ~Stoliki();
    void odnowianie();

private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_spinBox_2_valueChanged(int arg1);

    void on_pushButton_clicked();

    void on_spinBox_4_valueChanged(int arg1);

    void on_spinBox_3_valueChanged(int arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_spinBox_5_valueChanged(int arg1);

    void on_pushButton_5_clicked();

private:
    Ui::Stoliki *ui;
    QSqlDatabase db;
    QSqlTableModel *model;
    int NumerStolika;
    int iloscMejsc;
};

#endif // STOLIKI_H
