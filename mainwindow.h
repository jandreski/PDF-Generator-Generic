#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settings.h"
#include "about.h"
#include "eventsettings.h"
#include <vector>
#include <fstream>
#include <QFile>
#include <QTextStream>

//#include "utility.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Ui::MainWindow getUi();

    //get functions
    std::vector<int> getWhoSigns() {return whoSigns_; }
    std::vector<int> getGroupsChosen() {return groupsChosen_; }
    int getEventSelected() {return eventSelected_; }
    int getSignatureCounter() {return signatureCounter_; }

    void isItGeneratable();
    std::ofstream settingsFile;
    std::ofstream m_fin;

    int _groupsProcessed = 0;
    void makeList(std::ifstream &file);

    std::string letterContent();
    void placeholder_replace(std::string stiFe,std::string anDatum, std::string enDatum, std::string meldDatum);

    std::string placeSignatures();

private slots:
    void on_eventBox_currentIndexChanged(int index);
    void on_configBtn_clicked();

    void generalGroupSelect(int index, int arg);
    void on_G1_Ck_stateChanged(int arg1);
    void on_G2_Ck_stateChanged(int arg1);
    void on_G3_Ck_stateChanged(int arg1);
    void on_G4_Ck_stateChanged(int arg1);
    void on_G5_Ck_stateChanged(int arg1);
    void on_G6_Ck_stateChanged(int arg1);
    void on_G7_Ck_stateChanged(int arg1);
    void on_G8_Ck_stateChanged(int arg1);
    void on_G9_Ck_stateChanged(int arg1);
    void on_G10_Ck_stateChanged(int arg1);

    void signatureSelect(int index, int arg);

    void enableEventSettings(); //checks to see if the push butting is activated
    void on_eventSetting_clicked();
    void on_toSign1_stateChanged(int arg1);
    void on_toSign2_stateChanged(int arg1);
    void on_toSign3_stateChanged(int arg1);
    void on_toSign4_stateChanged(int arg1);
    void on_toSign5_stateChanged(int arg1);

    void on_aboutBtn_clicked();

    void on_instructionsBtn_clicked();


    void on_viewTemplateBtn_clicked();

    void on_generateBtn_clicked();

private:
    std::vector<int> whoSigns_; //selecting who signs the document ; MAX 2 ppl
    std::vector<int> groupsChosen_; //choosing who's invited
    int eventSelected_; //selecting the event
    int signatureCounter_; //counts how many ppl have signed

    bool PDFgeneratable;

    Ui::MainWindow *ui; //THIS window

    Settings *settingsScreen; // The settings window
};

#endif // MAINWINDOW_H
