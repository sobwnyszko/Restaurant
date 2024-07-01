#ifndef POTRAWY_H
#define POTRAWY_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>

namespace Ui {
class Potrawy;
}

class Potrawy : public QMainWindow
{
    Q_OBJECT

public:
    explicit Potrawy(QWidget *parent = nullptr);
    ~Potrawy();
    void odnowianie();

private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_lineEdit_editingFinished();

    void on_spinBox_2_valueChanged(int arg1);

    void on_doubleSpinBox_valueChanged(double arg1);

    void on_doubleSpinBox_2_valueChanged(double arg1);

    void on_spinBox_3_valueChanged(int arg1);

    void on_spinBox_4_valueChanged(int arg1);

    void on_spinBox_5_valueChanged(int arg1);

    void on_doubleSpinBox_3_valueChanged(double arg1);

    void on_doubleSpinBox_4_valueChanged(double arg1);

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Potrawy *ui;
    QSqlDatabase db;
    QSqlTableModel *modelPotrawy;
    QSqlTableModel *modelDania;
    int DanieID;
    int PotrawaID;
    QString Nazwa;
    int kalorii;
    double waga;
    double cena;
};

#endif // POTRAWY_H
