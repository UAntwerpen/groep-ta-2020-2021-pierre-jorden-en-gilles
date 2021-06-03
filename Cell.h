#ifndef TA_TO_CELL_H
#define TA_TO_CELL_H
#include "vector"
#include "cmath"
#include "Virus.h"
#include "map"

using namespace std;

class Cell {
private:
    int people;
    unsigned int healthy;
    unsigned int vaccinated;

    map<int, unsigned int> infected;

    unsigned int dead;

    bool quarantine;
    unsigned int days;
    unsigned int temp_people;
    unsigned int numberVaccinations;

    Virus* virus;

public:

    Cell(Virus* virus, int people);

    unsigned int getTotalInfected() const;

    int getPeople() const;

    unsigned int getVaccinated() const;

    unsigned int getDead() const;

    unsigned int getHealthy() const;

    void addInfected(int day, int amount);

    void setDead(unsigned int dead);

    void setVaccinated(unsigned int vaccinated);

    void removeHealthy(unsigned int healthy);

    void addHealthy(unsigned int healthy);

    void setQuarantine(bool quarantine);

    unsigned int getDays() const;

    void setDays(unsigned int days);

    bool isDead() const;

    bool isVaccinated() const;

    bool isQuarantined() const;

    bool hasHealthy() const;

    bool hasInfected() const;

    int cellDegree();

    static bool randomChance(double chance);

    double getISpread();

    double getRecovery(int i_day, int c_day);

    void internal(int day);

    void external_increase(unsigned int expeople);

};


#endif //TA_TO_CELL_H
