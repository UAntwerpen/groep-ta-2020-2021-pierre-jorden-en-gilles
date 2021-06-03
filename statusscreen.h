#ifndef STATUSSCREEN_H
#define STATUSSCREEN_H

#include <QDialog>

#include <string>

#include "System.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class statusScreen; }
QT_END_NAMESPACE

class statusScreen : public QDialog
{
    Q_OBJECT

public:
    statusScreen(QWidget *parent = nullptr, System *system = nullptr);
    ~statusScreen();

private slots:
    void on_exitButton_clicked();

    void on_resetButton_clicked();

    void on_continueButton_clicked();

    void on_chartButton_clicked();

private:
    Ui::statusScreen *ui;
    System *system;
};
#endif // STATUSSCREEN_H
