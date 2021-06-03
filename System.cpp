#include "System.h"

#include <QtWidgets>
#include "QMessageBox"
#include <iostream>
#include <string>

#include "board.h"
#include "virussettings.h"
#include "simulationsettings.h"
#include "statusscreen.h"
#include "graph.h"

using namespace  std;

/**
 * Constructor
 *
 * @param parent : needed for the GUI
 * @param people : amount of people in the system
 * @param width :
 * @param depth :
 */
System::System(QWidget* parent, int people, int width, int depth) : QMainWindow(parent) {
    peopleInit = people;
    widthInit = width;
    depthInit = depth;
    running = false;
    values = new vector<vector<unsigned int>>;
    status = "Simulation not started yet!";

    this->virus = new Virus();

    for (int i = 0; i < width; ++i) {
        vector<Cell*> vec(depth, nullptr);
        for (int j = 0; j < depth; ++j) {
            vec[j] = new Cell(virus, (people / (width*depth)));
        }
        this->cells.emplace_back(vec);
    }

    int r_i = rand() % width, r_j = rand()% depth;
    int r_people = rand() % (50) + 10;
    cells[r_i][r_j]->addInfected(1, r_people);
    cells[r_i][r_j]->removeHealthy(r_people);

    //cout << r_i << ", " << r_j << " : " << r_people << endl;

    scene = new Board(new QObject, width, depth);
    QGraphicsView *view = new QGraphicsView(scene);
    setCentralWidget(view);

    createActions();
    createMenus();

    scene->initialDraw();
    scene->updateBoard(cells);
    this->timer = new QTimer(this);
    speed = 1000;
}

/**
 * Run the simulation that was created
 * until either everyone is dead or cured
 */
void System::run() {
    vector<pair<int, int>> infected;

    for (int i = 0; i < cells.size(); ++i) {
        for (int j = 0; j < cells[i].size(); ++j) {
            if (cells[i][j]->hasInfected()){
                infected.emplace_back(make_pair(i, j));
            }
        }

    }
    for (int i = 0; i < cells.size(); ++i) {
        for (int j = 0; j < cells[i].size(); ++j) {
            //Quarantine
            if (cells[i][j]->cellDegree() >= (virus->getDegreeStep()-1) && !cells[i][j]->isQuarantined()){
                cells[i][j]->setQuarantine(true);
                cells[i][j]->setDays(virus->getQuarantine());
            } else if (cells[i][j]->getDays() == 0){
                cells[i][j]->setQuarantine(false);
            }
        }
    }
    // increase infect chance for al neighbors of infected cells
    // cells[i][j]infected/8
    for (auto coords : infected){
        if (!cells[coords.first][coords.second]->isQuarantined()){
            int people = ceil(cells[coords.first][coords.second]->getTotalInfected()/8); //minder kans om buitenaf te infecteren door grens maatregelen
            // half kans om een nieuwe cel te infecteren verspreiding virus

            //neighbors
            if (coords.second < cells[coords.first].size()-1){
                if (!cells[coords.first][coords.second+1]->isQuarantined()){
                    cells[coords.first][coords.second+1]->external_increase(people);
                }
            }

            if (coords.second >= 1){
                if (!cells[coords.first][coords.second-1]->isQuarantined()){
                    cells[coords.first][coords.second-1]->external_increase(people);
                }
            }

            if (coords.first < cells.size()-1){
                if (!cells[coords.first+1][coords.second]->isQuarantined()) {
                    cells[coords.first+1][coords.second]->external_increase(people);
                }

                if (coords.second < cells[coords.first].size()-1){
                    if (!cells[coords.first+1][coords.second+1]->isQuarantined()){
                        cells[coords.first+1][coords.second+1]->external_increase(people);
                    }
                }

                if (coords.second >= 1){
                    if (!cells[coords.first+1][coords.second-1]->isQuarantined()){
                        cells[coords.first+1][coords.second-1]->external_increase(people);
                    }
                }
            }

            if (coords.first >= 1){
                if (!cells[coords.first-1][coords.second]->isQuarantined()) {
                    cells[coords.first-1][coords.second]->external_increase(people);
                }

                if (coords.second < cells[coords.first].size()-1){
                    if (!cells[coords.first-1][coords.second+1]->isQuarantined()){
                        cells[coords.first-1][coords.second+1]->external_increase(people);
                    }
                }

                if (coords.second >= 1){
                    if (!cells[coords.first-1][coords.second-1]->isQuarantined()){
                        cells[coords.first-1][coords.second-1]->external_increase(people);
                    }
                }
            }

            int rx_path = int(rand() % ((cells.size() + 0) + 0)), ry_path = int(rand() % ((cells[0].size() + 0) + 0));
            if (!cells[rx_path][ry_path]->isQuarantined()){
                cells[rx_path][ry_path]->external_increase(people);
            }
        }
    }

    for (int i = 0; i < cells.size(); ++i) {
        for (int j = 0; j < cells[i].size(); ++j) {
            //Internal infection /deaths
            cells[i][j]->internal(current);
        }
    }

    this->current += 1;
    scene->updateBoard(cells);

    //Check if we need to stop the sim
    bool dead = true, cured = true, healthy = true, vdied = true;
    for (int i = 0; i < cells.size(); ++i) {
        for (int j = 0; j < cells[i].size(); ++j) {
            if (!cells[i][j]->isDead()){
                    dead = false;
            }
            if (!cells[i][j]->isVaccinated()) {
                cured = false;
            }
            if (cells[i][j]->hasInfected()
            && cells[i][j]->getHealthy() != (cells[i][j]->getPeople()-cells[i][j]->getDead()-cells[i][j]->getVaccinated())){
                if (cells[i][j]->getVaccinated() < cells[i][j]->getPeople()/2){
                    vdied = false;
                }
                healthy = false;
            }
        }
    }

    cout << "week: " << current << endl;
    // per week is niet meer per dag

        if (dead){
            cout << "Iedereen is dood" << endl;
            status = "Everybody died, unlucky.";
        } else if (cured){
            cout << "Iedereen is gevaccineert" << endl;
            status = "Everybody survived and got vaccinated.";
        } else if (healthy){
            if (vdied){
                cout << "People are getting vaccinated and the virus is dying out" << endl;
                status = "Most people got vaccinated and the virus died out.";
            } else {
                cout << "Iedereen is genezen" << endl;
                status = "Everybody survived because they are awesome!";
            }
        } else {
            cout << "continue sim" << endl;
        }

    if (dead or cured or healthy) {
        timer->stop();
        stats();
    }

    infected.clear();

    scene->updateBoard(cells);
    cout
    << "H: " << this->getHealthy() << " / " << peopleInit << ", "
    << "V: " << this->getVaccinated() << " / " << peopleInit << ", "
    << "I: " << this->getInfected() << " / " << peopleInit << ", "
    << "D: " << this->getDeaths() << " / " << peopleInit << endl;
    cout << "===================" << endl;

    values->push_back({this->getVaccinated(), this->getHealthy(), this->getInfected(), this->getDeaths()});
}

void System::Qrun() {
    if (!running) {
        running = true;
        status = "Simulation is running!";
        this->run();

        connect(timer, &QTimer::timeout, this, &System::run);
        timer->start(speed); // 4 second timer
    }
    else {
        bool timerWasRunning = false;
        if (timer->isActive()) {
            timer->stop();
            timerWasRunning = true;
        }
        QMessageBox::information(this, tr("Run Simulation"), tr("The simulation is already started!"));

        if (timerWasRunning) {
            timer->start(speed);
        }
    }
}

void System::simulationedit() {
    simulationSettings edit(this, &widthInit, &depthInit, &speed, &peopleInit);
    bool timerWasActive = false;
    if (timer->isActive()) {
        timer->stop();
        timerWasActive = true;
    }

    edit.setModal(true);
    edit.exec();

    if (timerWasActive) {
        timer->start(speed);
    }
    else if (!running){
        reset();
    }
}

void System::virusedit() {
    virusSettings edit(this, virus);

    bool timerWasActive = false;
    if (timer->isActive()){
        timer->stop();
        timerWasActive = true;
    }

    edit.setModal(true);
    edit.exec();

    if (timerWasActive) {
        timer->start(speed);
    }
}

void System::continueSim() {
    if (!timer->isActive() and running) {
        timer->start(speed);
    }
    else if (running) {
        timer->stop();
        QMessageBox::information(this, "ERROR", "The simulation is already active!");
        timer->start(speed);
    }
    else {
        QMessageBox::information(this, "ERROR", "The simulation is not yet started!");
    }
}

void System::pauseSim() {
    if (timer->isActive()) {
        timer->stop();
    }
    else {
        QMessageBox::information(this, "ERROR", "The simulation is not running!");
    }
}

void System::setSpeed() {
    bool timerWasActive = false;
    if (timer->isActive()) {
        timer->stop();
        timerWasActive = true;
    }
    speed = QInputDialog::getInt(this, "set simulation speed", "speed:", speed, 0, 5000);
    if (timerWasActive) {
        timer->start(speed);
    }
}

void System::resetSim() {
    bool timerWasActive = false;
    if (timer->isActive()) {
        timer->stop();
        timerWasActive = true;
    }

    if (QMessageBox::Yes == QMessageBox::question(this,
                                                  tr("Simulatie resetten"),
                                                  tr("Bent u zeker dat u de simulatie wilt resetten?")))
    {
        reset();
    }
    else if (timerWasActive) {
        timer->start(speed);
    }
}

unsigned int System::getVaccinated() const {
    unsigned int vac = 0;
    for (int i = 0; i < cells.size(); ++i) {
        for (int j = 0; j < cells[i].size(); ++j) {
            vac += cells[i][j]->getVaccinated();
        }
    }
    return vac;
}

unsigned int System::getHealthy() const {
    unsigned int healthy = 0;
    for (int i = 0; i < cells.size(); ++i) {
        for (int j = 0; j < cells[i].size(); ++j) {
            healthy += cells[i][j]->getHealthy();
        }
    }
    return healthy;
}

unsigned int System::getInfected() const {
    unsigned int infected = 0;
    for (int i = 0; i < cells.size(); ++i) {
        for (int j = 0; j < cells[i].size(); ++j) {
            infected += cells[i][j]->getTotalInfected();
        }
    }
    return infected;
}

unsigned int System::getDeaths() const {
    unsigned int deaths = 0;
    for (int i = 0; i < cells.size(); ++i) {
        for (int j = 0; j < cells[i].size(); ++j) {
            deaths += cells[i][j]->getDead();
        }
    }
    return deaths;
}

string System::getStatus() const {
    return status;
}

int System::getCurrent() const {
    return current;
}

void System::reset() {

    running = false;
    for (size_t i=0; i<cells.size(); i++) {
        for (size_t j=0; j<cells[i].size(); j++) {
            delete cells[i][j];
        }
        cells[i].resize(0);
    }
    cells.resize(0);
    delete timer;
    delete scene;
    delete values;

    timer = new QTimer(this);
    scene = new Board(new QObject, widthInit, depthInit);
    values = new vector<vector<unsigned int>>;

    for (int i = 0; i < widthInit; ++i) {
        vector<Cell*> vec(depthInit, nullptr);
        for (int j = 0; j < depthInit; ++j) {
            vec[j] = new Cell(virus, (peopleInit / (widthInit*depthInit)));
        }
        this->cells.emplace_back(vec);
    }

    int r_i = rand() % widthInit, r_j = rand() % depthInit;
    int r_people = rand() % (50) + 10;
    cells[r_i][r_j]->addInfected(1, r_people);
    cells[r_i][r_j]->removeHealthy(r_people);

    cout << r_i << ", " << r_j << " : " << r_people << endl;

    QGraphicsView *view = new QGraphicsView(scene);
    setCentralWidget(view);

    scene->initialDraw();
    scene->updateBoard(cells);

    current = 1;
}

void System::stats() {
    bool timerWasActive = false;
    if (timer->isActive()) {
        timer->stop();
        timerWasActive = true;
    }
    statusScreen statusscreen(this, this);
    statusscreen.setModal(true);
    statusscreen.exec();
    if (timerWasActive) {
        timer->start(speed);
    }
}

void System::getChart() {
    bool timerWasActive = false;
    if (timer->isActive()) {
        timer->stop();
        timerWasActive = true;
    }
    graph Chart(this, this);
    Chart.setModal(true);
    Chart.exec();
    if (timerWasActive) {
        timer->start(speed);
    }
}

vector<vector<unsigned int>>* System::getValues() const {
    return values;
}

int System::getPeopleInit() const {
    return peopleInit;
}

/**
 * @brief creates the menu actions for the GUI
 */
void System::createActions() {
    runSim = new QAction(tr("&Run until end"), this);
    runSim->setStatusTip(tr("running simulation"));
    connect(runSim, &QAction::triggered, this, &System::Qrun);

    simulationE = new QAction(tr("&Edit Simulation"), this);
    simulationE->setStatusTip(tr("Edit the simulation data"));
    connect(simulationE, &QAction::triggered, this, &System::simulationedit);

    virusE = new QAction(tr("Edit Virus"), this);
    virusE->setStatusTip(tr("Edit the virus data"));
    connect(virusE, &QAction::triggered, this, &System::virusedit);

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setStatusTip(tr("Abandon simulation"));
    connect(exitAct, &QAction::triggered, this, &System::exit);

    runAction = new QAction(tr("&Continue simulation"), this);
    runAction->setStatusTip(tr("running simulation"));
    connect(runAction, &QAction::triggered, this, &System::continueSim);

    pauseAction = new QAction(tr("&Pause simulation"), this);
    pauseAction->setStatusTip(tr("simulation paused"));
    connect(pauseAction, &QAction::triggered, this, &System::pauseSim);

    runSpeed = new QAction(tr("&Set simulation speed"), this);
    runSpeed->setStatusTip(tr("setting simulation speed"));
    connect(runSpeed, &QAction::triggered, this, &System::setSpeed);

    resetAction = new QAction(tr("&Reset simulation"), this);
    resetAction->setStatusTip(tr("resetting simulation"));
    connect(resetAction, &QAction::triggered, this, &System::resetSim);

    getStats = new QAction(tr("&status simulation"), this);
    getStats->setStatusTip(tr("getting status simulation"));
    connect(getStats, &QAction::triggered, this, &System::stats);

    showChart = new QAction(tr("&show chart"), this);
    showChart->setStatusTip(tr("viewing chart"));
    connect(showChart, &QAction::triggered, this, &System::getChart);
}

/**
 * @brief creates the menus for the GUI
 * 
 */
void System::createMenus() {
    simMenu = menuBar()->addMenu(tr("&Sim"));
    simMenu->addAction(runSim);
    simMenu->addAction(simulationE);
    simMenu->addAction(virusE);
    simMenu->addAction(runSpeed);
    simMenu->addAction(exitAct);

    runMenu = menuBar()->addMenu(tr("&Run"));
    runMenu->addAction(runAction);
    runMenu->addAction(pauseAction);
    runMenu->addAction(resetAction);
    runMenu->addAction(getStats);
    runMenu->addAction(showChart);
}


/**
 * @brief closes the GUI and the simulation
 * 
 */
void System::exit() {
    if (QMessageBox::Yes == QMessageBox::question(this,
                                                  tr("Simulatie verlaten"),
                                                  tr("Bent u zeker dat u de simulatie wil verlaten?")))
    {
        QApplication::quit();
    }
}



