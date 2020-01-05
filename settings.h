#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

private slots:
    void displayCurrentConfig();
    void updateConfig();
    void on_buttonBox_accepted();

    void on_unt1_clicked();
    void on_unt2_clicked();
    void on_unt3_clicked();
    void on_unt4_clicked();
    void on_unt5_clicked();

private:
    Ui::Settings *ui; //THIS window
};

#endif // SETTINGS_H
