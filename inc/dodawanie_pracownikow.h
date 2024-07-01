#ifndef DODAWANIE_PRACOWNIKOW_H
#define DODAWANIE_PRACOWNIKOW_H

#include <QMainWindow>
#include <QDate>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class Dodawanie_pracownikow;
}

class Dodawanie_pracownikow : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dodawanie_pracownikow(QWidget *parent = nullptr);
    ~Dodawanie_pracownikow();

private slots:
    void on_comboBox_textActivated(const QString &arg1);

    void on_lineEdit_2_editingFinished();

    void on_lineEdit_3_editingFinished();

    void on_lineEdit_4_editingFinished();

    void on_lineEdit_5_editingFinished();

    void on_lineEdit_6_editingFinished();

    void on_lineEdit_7_editingFinished();

    void on_lineEdit_8_editingFinished();

    void on_lineEdit_9_editingFinished();

    void on_lineEdit_10_editingFinished();

    void on_lineEdit_11_editingFinished();

    void on_lineEdit_12_editingFinished();

    void on_lineEdit_13_editingFinished();

    void on_dateEdit_userDateChanged(const QDate &date);

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_comboBox_2_textActivated(const QString &arg1);

    void on_lineEdit_14_editingFinished();

    void on_dateEdit_2_userDateChanged(const QDate &date);

    void on_pushButton_2_clicked();

private:
    Ui::Dodawanie_pracownikow *ui;
    QString rola;
    QString imie;
    QString nazwisko;
    QString PESEL;
    QString nrKotakt;
    QString mail;
    QString login;
    QString password;
    QString kodPocztowy;
    QString miasto;
    QString ulica;
    int nrDomu;
    int nrMieszkania;
    QDate dataZatrudninia;
    QDate dataZwolnienia;
    QSqlDatabase db;
};

#endif // DODAWANIE_PRACOWNIKOW_H
