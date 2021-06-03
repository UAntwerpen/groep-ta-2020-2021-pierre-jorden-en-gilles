/**
 *
 * @authors Pierre Franck, Jorden van Handenhoven, Gilles Kerstens
 *
 * 14/04/2021
 */

#include <iostream>
#include <QApplication>

#include "System.h"

using namespace std;


int main(int argc, char *argv[]){
    srand((unsigned) time(0));
    QApplication a(argc, argv);
    auto* sys = new System(new QWidget, 625000, 25, 25);
    sys->show();

    return a.exec();
}