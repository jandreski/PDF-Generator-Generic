#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <vector>
#include <QString>

#include "settings.h"
#include "ui_settings.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

//public variables

//static std::vector<int> publicWhoSigns_; //selecting who signs the document ; MAX 2 ppl
//static std::vector<int> publicGroupsChosen_; //choosing who's invited
//static int publicEventSelected_ = 100; //selecting the event
//static int publicSignatureCounter_; //counts how many ppl have signed

//globalizing if the generate button was pressed
static bool generateBtnPressed = false;

//to get current working directory of the project
std::string my_workingdir();
//converting the / into \\ for the filepath
std::string conv_fDash(std::string input);
//finding and replacing the signature images (PNGs only)
void signatureImgs(Ui::Settings *ui,std::string posToAlter, QString originalImgPath);
//Updating the preview box in MainWindow
void updatePreviewBox(Ui::MainWindow *ui);
//void updatePreviewBox();

//show the template preview
void showSamplePDF(std::string pathToSample);

#endif // UTILITY_H
