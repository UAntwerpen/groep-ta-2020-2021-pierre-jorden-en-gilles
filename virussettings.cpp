#include "virussettings.h"
#include "./ui_virussettings.h"

virusSettings::virusSettings(QWidget *parent, Virus *virus) : QDialog(parent), ui(new Ui::virusSettings), virus(virus) {
    ui->setupUi(this);

    ui->deathEdit->setPlaceholderText(QString::number(virus->getDChance()));
    ui->infectionEdit->setPlaceholderText(QString::number(virus->getIChance()));
    ui->recoveryEdit->setPlaceholderText(QString::number(virus->getRecoverySteps()));
    ui->recoveryMaxEdit->setPlaceholderText(QString::number(virus->getMaxRecoveryChance()));
    ui->degreeEdit->setPlaceholderText(QString::number(virus->getDegreeStep()));
    ui->delayEdit->setPlaceholderText(QString::number(virus->getVaccinationDelay()));
    ui->growthEdit->setPlaceholderText(QString::number(virus->getVaccinationGrowth()));
    ui->effectivenessEdit->setPlaceholderText(QString::number(virus->getVaccineEffectiveness()));
    ui->maxSpreadEdit->setPlaceholderText(QString::number(virus->getMaxSpreadChance()));
    ui->minSpreadEdit->setPlaceholderText(QString::number(virus->getMinSpreadChance()));
    ui->quarantineEdit->setPlaceholderText(QString::number(virus->getQuarantine()));
}

virusSettings::~virusSettings() {
    delete ui;
}

void virusSettings::on_okButton_clicked() {
    QString deathString = ui->deathEdit->text();
    QString infectionString = ui->infectionEdit->text();
    QString recoveryString = ui->recoveryEdit->text();
    QString maxRecoveryString = ui->recoveryMaxEdit->text();
    QString degreeString = ui->degreeEdit->text();
    QString delayString = ui->delayEdit->text();
    QString growthString = ui->growthEdit->text();
    QString effectivenessString = ui->effectivenessEdit->text();
    QString maxSpreadString = ui->maxSpreadEdit->text();
    QString minSpreadString = ui->minSpreadEdit->text();
    QString quarantineString = ui->quarantineEdit->text();

    if (deathString.size() == 0) {
        deathString = ui->deathEdit->placeholderText();
    }
    virus->setDChance(deathString.toDouble());
    if (infectionString.size() == 0) {
        infectionString = ui->infectionEdit->placeholderText();
    }
    virus->setIChance(infectionString.toDouble());
    if (recoveryString.size() == 0) {
        recoveryString = ui->recoveryEdit->placeholderText();
    }
    virus->setRecoverySteps(recoveryString.toInt());
    if (maxRecoveryString.size() == 0) {
        maxRecoveryString = ui->recoveryMaxEdit->placeholderText();
    }
    virus->setMaxRecoveryChance(maxRecoveryString.toDouble());
    if (degreeString.size() == 0) {
        degreeString = ui->degreeEdit->placeholderText();
    }
    virus->setDegreeStep(degreeString.toDouble());
    if (delayString.size() == 0) {
        delayString = ui->delayEdit->placeholderText();
    }
    virus->setVaccinationDelay(delayString.toInt());
    if (growthString.size() == 0) {
        growthString = ui->growthEdit->placeholderText();
    }
    virus->setVaccinationGrowth(growthString.toDouble());
    if (effectivenessString.size() == 0) {
        effectivenessString = ui->effectivenessEdit->placeholderText();
    }
    virus->setVaccineEffectiveness(effectivenessString.toDouble());
    if (maxSpreadString.size() == 0) {
        maxSpreadString = ui->maxSpreadEdit->placeholderText();
    }
    virus->setMaxSpreadChance(maxSpreadString.toDouble());
    if (minSpreadString.size() == 0) {
        minSpreadString = ui->minSpreadEdit->placeholderText();
    }
    virus->setMinSpreadChance(minSpreadString.toDouble());
    if (quarantineString.size() == 0) {
        quarantineString = ui->quarantineEdit->placeholderText();
    }
    virus->setQuarantine(quarantineString.toInt());

    this->close();
}


void virusSettings::on_cancelButton_clicked() {
    this->close();
}

