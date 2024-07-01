#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>

#include "kelner.h"
#include "kucharz.h"
#include "menedzer.h"
#include "sekretarka.h"
#include "dodawanie_pracownikow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_lineEdit_editingFinished();

    void on_lineEdit_2_editingFinished();

private:
    Ui::MainWindow *ui;
    QString login;
    QString password;
    Kelner *kelner;
    Kucharz *kucharz;
    Menedzer *menedzer;
    Sekretarka *sekretarka;
    QSqlDatabase db;
    Dodawanie_pracownikow *dodaj;
};
#endif // MAINWINDOW_H
