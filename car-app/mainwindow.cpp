#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnGet, &QPushButton::clicked, this, &MainWindow::btnGetSlot);
    manager = new QNetworkAccessManager(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::btnGetSlot()
{
    qDebug()<<"pushed";


    QString site_url = "http://127.0.0.1:3000/car";
    QNetworkRequest request(site_url);

    reply = manager->get(request);

    connect(reply, &QNetworkReply::finished,
            this, &MainWindow::getCarSlot);
}

void MainWindow::getCarSlot()
{
    response_data = reply->readAll();
    qDebug() << "DATA:" << response_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();

    ui->listWidget->clear();

    for (int i = 0; i < json_array.size(); i++)
    {
        QJsonObject json_obj = json_array[i].toObject();

        int id = json_obj["id_car"].toInt();
        QString brand = json_obj["branch"].toString();
        QString model = json_obj["model"].toString();

        QString car = QString::number(id) + " | " + brand + " " + model;

        ui->listWidget->addItem(car);
    }

    reply->deleteLater();
}
