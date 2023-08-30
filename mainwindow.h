#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_spectrum_rate_slider_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    QVector<double> x_, y_;
    QTimer *tr_;
    int interval_ = 1;

private slots:
    void UpdatePlot();
};
#endif // MAINWINDOW_H
