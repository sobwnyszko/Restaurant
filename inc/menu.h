#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>

namespace Ui {
class menu;
}

class menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = nullptr);
    ~menu();
    void odnowianie();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::menu *ui;
    QSqlDatabase db;
    QSqlTableModel *modelPotrawy;
    QSqlTableModel *modelDania;
};

#endif // MENU_H
