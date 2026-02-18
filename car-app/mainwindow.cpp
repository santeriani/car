#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnGet, &QPushButton::clicked, this, &MainWindow::btnGetSlot);
    manager = new QNetworkAccessManager(this);
    connect(ui->btnAdd, &QPushButton::clicked, this, &MainWindow::btnAddSlot);
    connect(ui->listWidget, &QListWidget::itemClicked, this, &MainWindow::CarSelected);
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

void MainWindow::btnAddSlot()
{
    QString branch = ui->TextCarBrand->text();
    QString model = ui->TextCarModel->text();

    QJsonObject json;
    json.insert("branch", branch);
    json.insert("model", model);

    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    QString site_url = "http://127.0.0.1:3000/car";
    QNetworkRequest request(site_url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    reply = manager->post(request, data);

    connect(reply, &QNetworkReply::finished,
            this, &MainWindow::addCarSlot);
}

void MainWindow::addCarSlot()
{
    QByteArray response = reply->readAll();
    qDebug() << "ADD RESPONSE:" << response;

    reply->deleteLater();
    btnGetSlot();

    ui->TextCarBrand->clear();
    ui->TextCarModel->clear();
}

void MainWindow::CarSelected()
{
    QString itemText = ui->listWidget->currentItem()->text();

    QString idPart = itemText.split("|")[0];
    selectedId = idPart.trimmed().toInt();

    qDebug() << "Selected ID:" << selectedId;
}


