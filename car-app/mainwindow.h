#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "environment.h"

#include <QMainWindow>

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
    void btnGetSlot();
    void getCarSlot();
    void btnAddSlot();
    void addCarSlot();
    void CarSelected();
    void btnDeleteSlot();
    void deleteCarSlot();
    void btnEditSlot();
    void editCarSlot();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QByteArray response_data;
    int selectedId = -1;

};
#endif
