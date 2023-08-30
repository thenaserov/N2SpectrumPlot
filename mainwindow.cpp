#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <chrono>
#include <ctime>
#include <QDebug>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    x_ = QVector<double>();
    y_ = QVector<double>();
    x_.resize(10000);
    y_.resize(10000);
    ui->spectrum_rate_slider->setMinimum(1);
    ui->spectrum_rate_slider->setMaximum(1000);
    ui->spectrum_rate_slider->grabMouse();
    ui->spectrum_widget->setBackground(QColor(50,50,50));
    ui->waterfall_widget->setBackground(QColor(0,0,0));
    ui->spectrum_widget->addGraph();
    ui->spectrum_widget->xAxis->setLabel("x");
    ui->spectrum_widget->yAxis->setLabel("y");
    ui->spectrum_widget->xAxis->setRange(0, 1000);
    ui->spectrum_widget->yAxis->setRange(-100, 300);
    ui->spectrum_widget->replot();
    tr_ = new QTimer();
    connect(tr_, &QTimer::timeout, this, &MainWindow::UpdatePlot);
    tr_->setInterval(interval_);
    tr_ ->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_spectrum_rate_slider_sliderMoved(int position)
{
    interval_ = position;
    tr_->setInterval(interval_);
}

void MainWindow::UpdatePlot()
{
    auto before = clock_t();
    for(int i{0}; i < 10000; i++)
    {
        x_[i] = QRandomGenerator::global()->bounded(1, 1000); // 0 to 15 Million
        y_[i] = QRandomGenerator::global()->bounded(1, 200);
    }
    auto after = clock_t();
    std::cout << after - before << std::endl;
    ui->spectrum_widget->graph(0)->setData(x_,y_);
    ui->spectrum_widget->replot();
}
