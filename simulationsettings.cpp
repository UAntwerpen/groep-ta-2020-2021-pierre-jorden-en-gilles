#include "simulationsettings.h"
#include "./ui_simulationsettings.h"

simulationSettings::simulationSettings(QWidget *parent, int *width, int *depth, int *speed, int *people) : QDialog(parent), ui(new Ui::simulationSettings),
    width(width), depth(depth), speed(speed), people(people) {
    ui->setupUi(this);

    ui->widthEdit->setPlaceholderText(QString::number(*width));
    ui->depthEdit->setPlaceholderText(QString::number(*depth));
    ui->speedEdit->setPlaceholderText(QString::number(*speed));
    ui->maxPeopleEdit->setPlaceholderText(QString::number(*people));
}

simulationSettings::~simulationSettings()
{
    delete ui;
}


void simulationSettings::on_okButton_clicked()
{
    QString widthString = ui->widthEdit->text();
    QString depthString = ui->depthEdit->text();
    QString speedString = ui->speedEdit->text();
    QString maxPeopleString = ui->maxPeopleEdit->text();

    if (widthString.size() == 0) {
        widthString = ui->widthEdit->placeholderText();
    }
    *width = widthString.toInt();
    if (depthString.size() == 0) {
        depthString = ui->depthEdit->placeholderText();
    }
    *depth = depthString.toInt();
    if (speedString.size() == 0) {
        speedString = ui->speedEdit->placeholderText();
    }
    *speed = speedString.toInt();
    if (maxPeopleString.size() == 0) {
        maxPeopleString = ui->maxPeopleEdit->placeholderText();
    }
    *people = maxPeopleString.toInt();

    this->close();
}


void simulationSettings::on_cancelButton_clicked()
{
    this->close();
}

