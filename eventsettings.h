#ifndef EVENTSETTINGS_H
#define EVENTSETTINGS_H
#include <string>
#include <iostream>
#include <sstream>

#include <QDialog>

namespace Ui {
class eventSettings;
}

class eventSettings : public QDialog
{
    Q_OBJECT

public:
    explicit eventSettings(QWidget *parent = nullptr);
    ~eventSettings();

private slots:
    void on_buttonBox_accepted();

    void on_unlockScheduleMaker_clicked();

    void on_updateSchedule_clicked();

private:
    Ui::eventSettings *ui;
    int _readEventSelected;
    std::string _anDatum, _enDatum, _meldDatum;
};

#endif // EVENTSETTINGS_H
