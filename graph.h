#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>
#include <QtCharts>
#include <QLineSeries>

#include "System.h"

namespace Ui {
class graph;
}

class graph : public QDialog
{
    Q_OBJECT

public:
    explicit graph(QWidget *parent = nullptr, System *system = nullptr);
    ~graph();

private slots:
    void on_pushButton_clicked();

private:
    Ui::graph *ui;
    System *system;

    QLineSeries *vaccinatedSeries;
    QLineSeries *healthySeries;
    QLineSeries *infectedSeries;
    QLineSeries *deathSeries;

    QChart *chart;
    QChartView *view;

    QValueAxis *axisX;
    QValueAxis *axisY;

};

#endif // GRAPH_H
