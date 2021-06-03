#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsScene>

#include "Cell.h"

class Board : public QGraphicsScene 
{
    Q_OBJECT
    
private:
    int rows;
    int columns;
    int tileWidth;
    int tileHeight;

public:
    explicit Board(QObject *parent, int rows, int columns);
    ~Board();

    void initialDraw();
    void drawTile(int row, int column, QColor color);
    void updateBoard(vector<vector<Cell *>> &cells);
};

#endif // BOARD_H