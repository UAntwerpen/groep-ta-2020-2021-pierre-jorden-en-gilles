#include "Virus.h"


/**
 * In our simulation we are going to use covid-19 as our virus
 */
Virus::Virus() {
    //TODO Correct virus data

    //data kans op sterfte bij covid = 0.5 % kans
    this->d_chance = 2.5; // .5 op 100

    // data kans op besmetting bij covid = 75 % als je in contact komt met een besmette persoon (factor is houden aan de maatregelen, antilichamen)
    this->i_chance = 75.0; //75 op 100

    // groeikans op besmetting zonder maatregelen is 25%  van de 3 nieuwe personen vaccineren
    // groeikans op besmetting met maatregelen is 10%
    this->spread_chance_max = 35.0;

    this->spread_chance_min = 10.0;

    //steps between max and min
    this->degreeStep = 5; // (step - 1) = QUARANTINE , ex: 5, on 4 : start quarantine

    // days to reach max recovery
    this->recovery_steps = 10;

    // maximum amount of chance to recover
    this->max_recovery_chance = 75.0;

    //Amount of days between first infection and first Vaccine
    this->vaccination_delay = 125;

    //Chance to get vaccinated (avg)
    this->vaccination_growth = 4.0;

    this->vaccine_effectiveness = 85.0;

    //amount of days a cell will be quarantined
    this->quarantine = 14;
}

/**
 * Get Virus chance of death
 *
 * @return double
 */
double Virus::getDChance() const {
    return d_chance;
}

/**
 * Get Virus chance of infection
 *
 * @return double
 */
double Virus::getIChance() const {
    return i_chance;
}

/**
 * Each step decreases the spread chance
 * Get the step value
 *
 * @return double
 */
double Virus::getDegreeStep() const {
    return this->degreeStep;
}

/**
 * Get the internal spread value
 *
 * @return double
 */
double Virus::getMaxSpreadChance() const {
    return this->spread_chance_max;
}

/**
 * Get the internal spread value
 *
 * @return double
 */
double Virus::getMinSpreadChance() const {
    return this->spread_chance_min;
}

/**
 * Get the steps (days) needed to reach max recovery
 *
 * @return integer
 */
int Virus::getRecoverySteps() const {
    return recovery_steps;
}

/**
 * Get the max recovery chance
 *
 * @return
 */
double Virus::getMaxRecoveryChance() const {
    return max_recovery_chance;
}

/**
 * Get the chance to recover from the virus
 *
 * @return double
 */
double Virus::getRecoverChance() const {
    return getMaxRecoveryChance()/getRecoverySteps();
}

/**
 * Get the delay between first infection and first Vaccine
 *
 * @return integer
 */
int Virus::getVaccinationDelay() const {
    return this->vaccination_delay;
}

/**
 * Get the Vaccination growth
 *
 * @return double
 */
double Virus::getVaccinationGrowth() const {
    return this->vaccination_growth;
}

double Virus::getVaccineEffectiveness() const {
    return vaccine_effectiveness;
}

int Virus::getQuarantine() const {
    return quarantine;
}

void Virus::setDChance(double dChance) {
    d_chance = dChance;
}

void Virus::setIChance(double iChance) {
    i_chance = iChance;
}

void Virus::setMaxSpreadChance(double maxSpreadChance) {
    spread_chance_max = maxSpreadChance;
}

void Virus::setMinSpreadChance(double minSpreadChance) {
    spread_chance_min = minSpreadChance;
}

void Virus::setDegreeStep(double degreeStep) {
    Virus::degreeStep = degreeStep;
}

void Virus::setVaccinationDelay(int vaccinationDelay) {
    vaccination_delay = vaccinationDelay;
}

void Virus::setVaccinationGrowth(double vaccinationGrowth) {
    vaccination_growth = vaccinationGrowth;
}

void Virus::setMaxRecoveryChance(double maxRecoveryChance) {
    max_recovery_chance = maxRecoveryChance;
}

void Virus::setRecoverySteps(int recoverySteps) {
    recovery_steps = recoverySteps;
}

void Virus::setVaccineEffectiveness(double vaccineEffectiveness) {
    vaccine_effectiveness = vaccineEffectiveness;
}

void Virus::setQuarantine(int quarantine) {
    Virus::quarantine = quarantine;
}


