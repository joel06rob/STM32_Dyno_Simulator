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

MainWindow::~MainWindow()
{
    delete ui;
}