#include "statusscreen.h"
#include "./ui_statusscreen.h"

#include <math.h>

using namespace std;

statusScreen::statusScreen(QWidget *parent, System *system)
    : QDialog(parent)
    , ui(new Ui::statusScreen), system(system)
{
    ui->setupUi(this);

    ui->resultText->setText(QString::fromStdString(system->getStatus()
        + "\n\n\n Week: "+ to_string(system->getCurrent())));
    ui->vaccinatedBar->setMinimum(0);
    ui->vaccinatedBar->setMaximum(100);
    ui->healthyBar->setMinimum(0);
    ui->healthyBar->setMaximum(100);
    ui->infectedBar->setMinimum(0);
    ui->infectedBar->setMaximum(100);
    ui->deathBar->setMinimum(0);
    ui->deathBar->setMaximum(100);

    int total = system->getDeaths() + system->getInfected() + system->getHealthy() + system->getVaccinated();
    int vaccinatedP = round((double) 100 * (double) system->getVaccinated() / (double) total);
    int healthyP = round((double) 100 * (double) system->getHealthy() / (double) total);
    int infectedP = round((double) 100 * (double) system->getInfected() / (double) total);
    int deathP = round((double) 100 * (double) system->getDeaths() / (double) total);

    ui->vaccinatedBar->setValue(vaccinatedP);
    ui->healthyBar->setValue(healthyP);
    ui->infectedBar->setValue(infectedP);
    ui->deathBar->setValue(deathP);
}

statusScreen::~statusScreen()
{
    delete ui;
}


void statusScreen::on_exitButton_clicked()
{
    QApplication::quit();
}


void statusScreen::on_resetButton_clicked()
{
    this->close();
    system->reset();
}

void statusScreen::on_continueButton_clicked()
{
    this->close();
}


void statusScreen::on_chartButton_clicked()
{
    system->getChart();
}

