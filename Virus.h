#ifndef TA_TO_VIRUS_H
#define TA_TO_VIRUS_H


class Virus {

private:

    double d_chance;
    double i_chance;
    double spread_chance_max;
    double spread_chance_min;
    double degreeStep;
    double max_recovery_chance;
    int recovery_steps;

    int vaccination_delay;
    double vaccination_growth;
    double vaccine_effectiveness;
    int quarantine;

public:
    Virus();

    double getDChance() const;

    double getIChance() const;

    double getMaxSpreadChance() const;

    double getMinSpreadChance() const;

    double getMaxRecoveryChance() const;

    int getRecoverySteps() const;

    double getRecoverChance() const;

    double getDegreeStep() const;

    int getVaccinationDelay() const;

    double getVaccinationGrowth() const;

    int getQuarantine() const;

    void setDChance(double dChance);

    void setIChance(double iChance);

    void setMaxSpreadChance(double maxSpreadChance);

    void setMinSpreadChance(double minSpreadChance);

    void setDegreeStep(double degreeStep);

    void setVaccinationDelay(int vaccinationDelay);

    void setVaccinationGrowth(double vaccinationGrowth);

    void setMaxRecoveryChance(double maxRecoveryChance);

    void setRecoverySteps(int recoverySteps);

    void setVaccineEffectiveness(double vaccineEffectiveness);

    double getVaccineEffectiveness() const;

    void setQuarantine(int quarantine);
};


#endif //TA_TO_VIRUS_H
