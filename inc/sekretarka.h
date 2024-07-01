#ifndef SEKRETARKA_H
#define SEKRETARKA_H

#include <QMainWindow>
#include <QDate>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>

namespace Ui {
class Sekretarka;
}

class Sekretarka : public QMainWindow
{
    Q_OBJECT

public:
    explicit Sekretarka(QWidget *parent = nullptr);
    ~Sekretarka();
    void setID(int id){
        this->ID = id;
    }
    void odnowianie();

private slots:
    void on_pushButton_3_clicked();

    void on_dateEdit_userDateChanged(const QDate &date);

    void on_timeEdit_userTimeChanged(const QTime &time);

    void on_spinBox_valueChanged(int arg1);

    void on_lineEdit_editingFinished();

    void on_lineEdit_2_editingFinished();

    void on_lineEdit_3_editingFinished();

    void on_spinBox_3_valueChanged(int arg1);

    void on_comboBox_textActivated(const QString &arg1);

    void on_dateEdit_2_userDateChanged(const QDate &date);

    void on_timeEdit_2_userTimeChanged(const QTime &time);

    void on_spinBox_2_valueChanged(int arg1);

    void on_lineEdit_5_editingFinished();

    void on_lineEdit_6_editingFinished();

    void on_lineEdit_4_editingFinished();

    void on_spinBox_4_valueChanged(int arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Sekretarka *ui;
    int ID;
    QSqlDatabase db;
    QSqlTableModel *model;
    int IDRezerwacji;
    QString CoZmienic;
    QDate data;
    QTime time;
    int NrStolika;
    QString imie;
    QString nazwisko;
    QString NrKontaktowy;
};

#endif // SEKRETARKA_H
