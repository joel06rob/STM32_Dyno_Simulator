#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QPainter>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //=============================
    //TEST: Serial port
    serial = new QSerialPort(this);

    //Serial configs
    serial->setPortName("/dev/tty.usbmodem103");
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    //Serial connect readyRead - Whenever serial emits a read signal call the readSerialData() on this MainWindow
    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readSerialData);

    //Open serial port
    if (serial->open(QIODevice::ReadOnly)){

        qDebug() << "Serial port open!";

    }
    else{

        qDebug() << "Serial port error!" << serial->errorString();

    }





    //TEST: Line 1
    QLineSeries *series1 = new QLineSeries();
    series1->setName("Temperature");

    series1->append(0, 2);
    series1->append(1, 5);
    series1->append(2, 3);
    series1->append(3, 8);
    series1->append(4, 6);


    //TEST: Line 2
    QLineSeries *series2 = new QLineSeries();
    series2->setName("Pressure");

    series2->append(0, 7);
    series2->append(1, 6);
    series2->append(2, 8);
    series2->append(3, 4);
    series2->append(4, 9);


    //Create QChart
    QChart *chart = new QChart();

    chart->addSeries(series1);
    chart->addSeries(series2);

    //Create axes that work for both series
    chart->createDefaultAxes();

    chart->setTitle("Sensor Data");
    chart->setBackgroundBrush(QColor(38,38,38));
    chart->setTitleBrush(QColor(255,255,255));


    //Display QChart on window
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    //Layout for chartContainer
    QVBoxLayout *chartLayout = new QVBoxLayout(ui->chartContainer);
    //Add chart to created layout
    chartLayout->addWidget(chartView);

    //TEST: Dashboard values
    ui->rpmLabel->setText("4500");
    ui->tempLabel->setText("92 *C");
    ui->powerLabel->setText("200 BHP");
}

void MainWindow::readSerialData()
{
    //Add received bytes to buffer
    serialBuffer.append(serial->readAll());

    //Loop through received bytes - splitting on new line character (end of msg)
    while (serialBuffer.contains('\n')){

        int newlineIndex = serialBuffer.indexOf('\n');

        //Get the full message from start to new line char
        QByteArray line = serialBuffer.left(newlineIndex);

        //Remove extracted msg
        serialBuffer.remove(0, newlineIndex + 1);

        //Store the full message line as a string
        QString msg = QString::fromUtf8(line).trimmed();

        qDebug().noquote() << "Received: " << msg;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}