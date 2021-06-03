#include "Cell.h"
#include <iostream>
#include "string"


/**
 * Constructor for a cell
 *
 * @param people : amount of people in this cell
 */
Cell::Cell(Virus* virus, int people) : people(people), virus(virus) {
    this->healthy = people;
    this->dead = 0;
    this->infected = map<int, unsigned int>();
    this->vaccinated = 0;
    this->quarantine = false;
    this->days = 0;
    this->temp_people = 0;
    this->numberVaccinations = ceil((people)/200);
}

/**
 * Get the total amount of infected people
 * @return
 */
unsigned int Cell::getTotalInfected() const{
    unsigned int total = 0;
    for (auto pair : infected){
        total += pair.second;
    }
    return total;
}

void Cell::addInfected(int day, int amount) {
    this->infected.insert(make_pair(day, amount));
}

/**
 * Get the total amount of people in this cell
 * regardless of status (dead, infected, cured, healthy)
 *
 * @return integer
 */
int Cell::getPeople() const {
    return this->people;
}

/**
 * Get the amount of vaccinated people in this cell
 *
 * @return integer
 */
unsigned int Cell::getVaccinated() const {
    return this->vaccinated;
}

/**
 * Set the amount of vaccinated people
 *
 * @param vacinated : integer value
 */
void Cell::setVaccinated(unsigned int vaccinated) {
    if (0 > vaccinated){
        this->vaccinated =0;
    } else if( vaccinated > this->people){
        this->vaccinated = people;
    } else {
        this->vaccinated = vaccinated;
    }
}

/**
 * Get the amount of dead people in this cell
 *
 * @return integer
 */
unsigned int Cell::getDead() const {
    return this->dead;
}

/**
 * Set the amount of dead people
 *
 * @param dead : integer value
 */
void Cell::setDead(unsigned int dead) {
    if (0 > dead){
        this->dead =0;
    } else if( dead > this->people){
        this->dead = people;
    } else {
        this->dead = dead;
    }
}

/**
 * Check if the cell is dead (no people alive)
 *
 * @return boolean [TRUE/FALSE]
 */
bool Cell::isDead() const {
    if (this->dead == this->people){
        return true;
    }
    return false;
}

/**
 * Check if the cell is Vaccinted (remaing people)
 *
 * @return boolean [TRUE/FALSE]
 */
bool Cell::isVaccinated() const {
    if (this->vaccinated == this->people - this->dead){
        return true;
    }
    return false;
}

/**
 * Set the quarantine
 *
 * @param quarantine : boolean
 */
void Cell::setQuarantine(bool quarantine) {
    this->quarantine = quarantine;
}

/**
 * See if the cell is Quarantined
 *
 * @return boolean [TRUE/FALSE]
 */
bool Cell::isQuarantined() const {
    return this->quarantine;
}

/**
 * Get the days the cell is in quarantine
 *
 * @return integer
 */
unsigned int Cell::getDays() const {
    return days;
}

/**
 * Set the amount of days in quarantine
 *
 * @param days : integer
 */
void Cell::setDays(unsigned int days) {
    this->days = days;
}

/**
 * Get the amount of health people in the cell
 *
 * @return integer
 */
unsigned int Cell::getHealthy() const {
    return healthy;
}

/**
 * Add the given amount of healthy people to the total
 *
 * @param healthy : unsigned integer
 */
void Cell::addHealthy(unsigned int healthy) {
    if (healthy + this->healthy > this->people){
        this->healthy = people;
    } else{
        this->healthy += healthy;
    }
}

/**
 * remove healthy people for the total (they were vaccinated, infected or died)
 *
 * @param healthy : unsigned integer
 */
void Cell::removeHealthy(unsigned int healthy) {
    if (healthy >= this->healthy){
        this->healthy = 0;
    } else if (this->healthy - healthy > this->people){
        this->healthy = 0;
    } else {
        this->healthy -= healthy;
    }
}

/**
 * Check if the cell has infected people
 *
 * @return boolean [TRUE/FALSE]
 */
bool Cell::hasInfected() const {
    if (this->getTotalInfected() > 0){
        return true;
    }
    return false;
}

/**
 * Check if the cell has healthy people
 *
 * @return boolean [TRUE/FALSE]
 */
bool Cell::hasHealthy() const {
    if (this->healthy > 0){
        return true;
    }
    return false;
}


// vanaf hier de echte berekeningen

/**
 * increase the possibility of this cell's infections
 *
 * @param chance : double
 */
void Cell::external_increase(unsigned int expeople) {
    int newPeopleInfected = 0;

    if (!isQuarantined()){
        for (int i = 0; i < expeople; ++i) {
            if (randomChance(getISpread())){
                newPeopleInfected += 1;
            }
        }
        if (newPeopleInfected > people){
            newPeopleInfected = people;
        }
    }
    this->temp_people += newPeopleInfected;
}

/**
 * bereken hoe groot de graad is van maatregelen
 *
 * degree :
 * 1 : distance, masks
 * 2 : Essentials shops
 * 3 : Quarantine, ...
 * 4 : .....
 *
 * @return graad van 0-4
 */
int Cell::cellDegree() {
    int temp = 0;
    for (int i = 0; i < virus->getDegreeStep(); ++i) {
        if ((people * (i/virus->getDegreeStep())) <= this->getTotalInfected() &&
                this->getTotalInfected() < (people * ((i+1)/virus->getDegreeStep()))){
            temp = i;
            return i;

        }
    }
    return temp;
}

/**
 * Get the Infection rate inside this cell
 *
 * @return double
 */
double Cell::getISpread() {
    if (isQuarantined()){
        return virus->getMinSpreadChance();
    }
    double chance = (virus->getMaxSpreadChance() - virus->getMinSpreadChance()) / virus->getDegreeStep();
    return (this->virus->getMaxSpreadChance() - (cellDegree() * chance));
}

/**
 * Calculate the recovery chance based on the current and infection current
 *
 * @param i_day : infection current (when where the people infected)
 * @param c_day : current current (what's the current current of the sim)
 *
 * @return double :
 */
double Cell::getRecovery(int i_day, int c_day){
    if (virus->getRecoverChance() * (c_day-i_day) >= virus->getMaxRecoveryChance()){
        return virus->getMaxRecoveryChance();
    } else {
        return (virus->getRecoverChance() * (c_day-i_day));
    }
}

/**
 * Check if you're unlucky (0-100)
 *
 * @param chance : double : chance to compare it too
 * @return boolean [TRUE/FALSE]
 */
bool Cell::randomChance(double chance) {
    return ((0+(double) (rand()) / ((double) (RAND_MAX/(100-0)))) <= chance);
}

/**
 * Internal cell mechanics (spread & deaths)
 */
void Cell::internal(const int day) {
    int newGrowth = 0;
    int newDeaths = 0;
    int newInfected = 0;
    int newRecoveries = 0;
    int newVaccinations = 0;

    auto it = infected.find(day);
    if(it == infected.end()){
        infected.insert(make_pair(day, 0));
    }

    if (!this->isDead() && this->hasHealthy() && (hasInfected() or temp_people != 0)){
        if (isQuarantined()){ //no external when in quarantine
            temp_people = 0;
        }
        for (int i = 0; i < this->getTotalInfected() + temp_people; ++i) {
            if (randomChance(getISpread())){ //Lowest chance when in quarantine
                if (newGrowth == (people-dead-vaccinated-getTotalInfected())){
                    break;
                } else { // hier verandert normaal heel de tijd + 2
                    if (rand()%100 < 55){
                        newGrowth += 2;
                    }else{
                        newGrowth += 1;
                    }
                }
            }
        }
        for (int i = 0; i < newGrowth; ++i) {
            if (randomChance(virus->getIChance())){
                if (newInfected + this->getTotalInfected() == (people-dead-vaccinated)){
                    break;
                }
                newInfected += 1;
            }
        }
    }
    removeHealthy(newInfected);

    if (hasInfected()){
        for (auto pair : infected){
            for (int i = 0; i < pair.second; ++i) {
                if (randomChance(virus->getDChance()) && (day - pair.first)%10 == 0){
                    newDeaths += 1;
                } else if (randomChance(this->getRecovery(pair.first, day))){
                    newRecoveries += 1;
                }
            }
            this->infected.at(pair.first) -= (newDeaths + newRecoveries);
            setDead(dead + newDeaths);
            addHealthy(newRecoveries);
            removeHealthy(newDeaths);
            newDeaths = 0;
            newRecoveries = 0;
        }
    }

    unsigned int vacs = 0;
    if (virus->getVaccinationDelay() <= day){ // check if you're able to vaccinate
        if (day % 31 == 0){ // om de ongeveer 1 week kunnen ze meer personen vaccineren wat gelijk is aan de vaccinatiegroei
            this->numberVaccinations += int(this->numberVaccinations * (this->virus->getVaccinationGrowth()/100));
        }
        if (getTotalInfected() + getHealthy() < this->numberVaccinations){
            this->numberVaccinations = getTotalInfected() + getHealthy();
        }
        for (int i = 0; i < this->numberVaccinations; ++i) {
            if (randomChance(99)){ // de kans dat een individu komt opdagen voor zijn vaccin
                if (randomChance(virus->getVaccineEffectiveness())){
                    newVaccinations += 1;
                }
            }
        }
        vacs = newVaccinations;
        for (auto pair : infected) { // current : newinfected
            if (pair.second < newVaccinations){
                newVaccinations -= pair.second;
                infected.at(pair.first) = 0;
            } else {
                infected.at(pair.first) -= newVaccinations;
                newVaccinations = 0;
            }
        }

        if (newVaccinations > 0){
            if (healthy < newVaccinations){
                //cout << "HELP: "<< healthy << " : " << newVaccinations << endl;
            }
            removeHealthy(newVaccinations);
        }
    }

    setVaccinated(vaccinated + vacs);
    this->infected.at(day) += newInfected;

    /* cout
     << "I: " << newInfected     << " : " << this->getTotalInfected()   << " / " << this->people << endl
     << "R: " << newRecoveries   << " : " << this->healthy    << " / " << this->people << endl
     << "D: " << newDeaths       << " : " << this->dead       << " / " << this->people << endl
     << "V: " << newVaccinations << " : " << this->vaccinated << " / " << this->people << endl;

     cout << "===================" << endl;*/

     //cleanup infected
     vector<int> keys;
     for (auto pair : infected){
         if (pair.second <= 0){
             keys.emplace_back(pair.first);
         }
     }
     for (int key : keys){
         infected.erase(key);
     }
     keys.clear();

     temp_people = 0;

     if (isQuarantined()) {
        //cout << days <<endl;
        this->days -= 1;
        //cout <<"current:"<< days <<endl;
     }
 }

 // na 334 dagen eerste vaccin kunnen zetten


