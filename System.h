#ifndef TA_TO_SYSTEM_H
#define TA_TO_SYSTEM_H

#include <QMainWindow>

#include <string>

#include "QTimer"
#include "Cell.h"
#include "Virus.h"

using namespace std;

class Board;
class QSettings;

class System : public QMainWindow {
    Q_OBJECT

private:
    // initial values
    int peopleInit;
    int widthInit;
    int depthInit;
    bool running;
    string status;

    vector<vector<Cell*>> cells;
    int current =1;
    Virus* virus;
    int speed;
    vector<vector<unsigned int>> *values;

    Board* scene;

    //Timer
    QTimer* timer;

    // menus
    QMenu *simMenu;
    QMenu *runMenu;

    // Actions
    QAction *runSim;
    QAction *exitAct;
    QAction *simulationE;
    QAction *virusE;
    QAction *pauseAction;
    QAction *runAction;
    QAction *runSpeed;
    QAction *resetAction;
    QAction *getStats;
    QAction *showChart;

public:
    System(QWidget* parent, int people, int width, int depth);
    //~System();

    void run();

    void Qrun();
    void simulationedit();
    void virusedit();
    void continueSim();
    void pauseSim();
    void setSpeed();
    void resetSim();
    void reset();
    void stats();
    void getChart();
    int getCurrent() const;

    unsigned int getVaccinated() const;
    unsigned int getHealthy() const;
    unsigned int getInfected() const;
    unsigned int getDeaths() const;
    string getStatus() const;
    vector<vector<unsigned int>>* getValues() const;
    int getPeopleInit() const;

private: // functions
    void createActions();
    void createMenus();
    void exit();

};


#endif //TA_TO_SYSTEM_H
