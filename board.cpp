#include "board.h"

#include <QtWidgets>
#include <QPixmap>

#include <fstream>
#include <iostream>
using namespace std;

Board::Board(QObject *parent, int rows, int columns) : QGraphicsScene(parent), rows(rows), columns(columns)
{
    tileWidth = 900 / columns;
    tileHeight = 900 / rows;
};

Board::~Board() {};

void Board::initialDraw()
{
    for (int r=0; r<rows; r++) {
        for (int c=0; c<columns; c++) {
            drawTile(r, c, QColor(0, 255, 0));
        }
    }
}

void Board::drawTile(int row, int column, QColor color)
{
    QGraphicsRectItem *rect = new QGraphicsRectItem( (row * tileHeight), (column * tileWidth),
                                                     tileHeight, tileWidth);

    rect->setBrush(QBrush(color, Qt::SolidPattern));
    rect->setCacheMode(QGraphicsItem::NoCache);
    rect->update( (row * tileHeight), (column * tileWidth), tileHeight, tileWidth);
    addItem(rect);

    QGraphicsItem *item = itemAt((row * tileWidth), (column * tileHeight), QTransform());
    
    if (item == 0) {
        cout << "no item added" << endl;
    }
}

void Board::updateBoard(vector<vector<Cell *>> &cells) {
    for (int i=0; i<rows; i++) {
        for (int j=0; j<columns; j++) {
            delete itemAt((i * tileWidth), (j * tileHeight), QTransform());
        }
    }
    
    for (int i=0; i<rows; i++) {
        for (int j=0; j<columns; j++) {
            int total = cells[i][j]->getPeople();

            double percV = ((double) cells[i][j]->getVaccinated()) / ((double) total);
            double percH = ((double) cells[i][j]->getHealthy()) / ((double) total);
            double percI = ((double) cells[i][j]->getTotalInfected()) / ((double) total);
            double percD = ((double) cells[i][j]->getDead()) / ((double) total);
            
            int red = int(255 * percI);
            int green = int(255 * percH);
            int blue = int(255 * percV);

            QGraphicsRectItem *rect = new QGraphicsRectItem((i * tileHeight), (j * tileWidth), tileHeight, tileWidth);
            rect->setBrush(QBrush(QColor(red, green, blue), Qt::SolidPattern));
            rect->setCacheMode(QGraphicsItem::NoCache);

            addItem(rect);
        }
    }
}