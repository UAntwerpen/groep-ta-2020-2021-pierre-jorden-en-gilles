#include "graph.h"
#include "ui_graph.h"

graph::graph(QWidget *parent, System *system) : QDialog(parent), ui(new Ui::graph),
    system(system) {
    ui->setupUi(this);

    axisX = new QValueAxis;
    axisX->setTitleText("Weeks");
    axisX->setRange(0, system->getCurrent());
    axisY = new QValueAxis;
    axisY->setTitleText("People");
    axisY->setRange(0, (system->getPeopleInit()));

    chart = new QChart();
    view = new QChartView(chart);

    vaccinatedSeries = new QLineSeries();
    healthySeries = new QLineSeries();
    infectedSeries = new QLineSeries();
    deathSeries = new QLineSeries();

    vector<vector<unsigned int>> *values = system->getValues();

    for (unsigned int i=0; i<values->size(); i++) {
        vaccinatedSeries->append(i, (*values)[i][0]);
        healthySeries->append(i, (*values)[i][1]);
        infectedSeries->append(i, (*values)[i][2]);
        deathSeries->append(i, (*values)[i][3]);
    }
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    chart->addSeries(vaccinatedSeries);
    vaccinatedSeries->setName("Vaccinated");
    vaccinatedSeries->attachAxis(axisX);
    vaccinatedSeries->attachAxis(axisY);
    vaccinatedSeries->setColor(QColor(0, 0, 255));

    chart->addSeries(healthySeries);
    healthySeries->setName("Healthy");
    healthySeries->attachAxis(axisX);
    healthySeries->attachAxis(axisY);
    healthySeries->setColor(QColor(0, 255, 0));

    chart->addSeries(infectedSeries);
    infectedSeries->setName("Infected");
    infectedSeries->attachAxis(axisX);
    infectedSeries->attachAxis(axisY);
    infectedSeries->setColor(QColor(255, 0, 0));

    chart->addSeries(deathSeries);
    deathSeries->setName("Deaths");
    deathSeries->attachAxis(axisX);
    deathSeries->attachAxis(axisY);
    deathSeries->setColor(QColor(1, 1, 1));

    chart->setTitle("data");
    view->setRenderHint(QPainter::Antialiasing);
    view->setParent(ui->chart);
    view->setMinimumSize(QSize(1062, 671));
    view->setMaximumSize(QSize(1062, 671));
}

graph::~graph()
{
    delete ui;

    delete vaccinatedSeries;
    delete healthySeries;
    delete infectedSeries;
    delete deathSeries;

    delete chart;
    delete view;
}


void graph::on_pushButton_clicked()
{
    this->close();
}

