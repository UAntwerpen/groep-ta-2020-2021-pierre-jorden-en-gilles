#ifndef SIMULATIONSETTINGS_H
#define SIMULATIONSETTINGS_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class simulationSettings; }
QT_END_NAMESPACE

class simulationSettings : public QDialog
{
    Q_OBJECT

public:
    simulationSettings(QWidget *parent = nullptr, int *width = nullptr, int *depth = nullptr, int *speed = nullptr, int *people = nullptr);
    ~simulationSettings();

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::simulationSettings *ui;
    int *width;
    int *depth;
    int *speed;
    int *people;
};
#endif // SIMULATIONSETTINGS_H
