#ifndef VIRUSSETTINGS_H
#define VIRUSSETTINGS_H

#include <QDialog>

#include "Virus.h"

QT_BEGIN_NAMESPACE
namespace Ui { class virusSettings; }
QT_END_NAMESPACE

class virusSettings : public QDialog
{
    Q_OBJECT

public:
    virusSettings(QWidget *parent = nullptr, Virus *virus = nullptr);
    ~virusSettings();

private slots:
    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::virusSettings *ui;
    Virus *virus;
};
#endif // VIRUSSETTINGS_H
