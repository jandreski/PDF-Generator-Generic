#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settings.h"
#include "utility.h"
#include "eventsettings.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <sstream>
#include <ctime>

//#include "utility.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //my inputs

    //disable preview template button by default
    ui->viewTemplateBtn->setEnabled(false);
    //Initiallize the groupsChosen vector
    groupsChosen_ = {0,0,0,0,0,0,0,0,0,0};
    //Initiallize whoSigns_
    whoSigns_ = {0,0,0,0,0};
    signatureCounter_ = 0;
    //show current config in preview box
    updatePreviewBox(ui);

}



MainWindow::~MainWindow()
{
    m_fin.close();
    delete ui;
}

Ui::MainWindow MainWindow::getUi() {
    return *ui;
}

void MainWindow::on_eventBox_currentIndexChanged(int index)
{
    if(index == 0){
        ui->viewTemplateBtn->setEnabled(false);
    } else {
        ui->viewTemplateBtn->setEnabled(true);
    }
    eventSelected_ = index;

    enableEventSettings(); //Checking if the event settings box needs to be enabled.


    isItGeneratable();
}

void MainWindow::on_configBtn_clicked()
{
    settingsScreen = new Settings(this);
    settingsScreen->exec();
}

void MainWindow::generalGroupSelect(int index, int arg){
    if(arg == 0) {
        groupsChosen_[index] = 0;
    }
    else {
        groupsChosen_[index] = 1;

        //ui->G3_Ck->isChecked();
        //groupsChosen_[2] = 1;
    }
    //print out current config
    for (int i = 0;i<10;i++) {
        cout << groupsChosen_[i] << "  ";
        if(i == 9){
            cout << endl;
        }
    }

    isItGeneratable();
}

void MainWindow::on_G1_Ck_stateChanged(int arg1) { this->generalGroupSelect(0,arg1); }

void MainWindow::on_G2_Ck_stateChanged(int arg1) { this->generalGroupSelect(1,arg1); }

void MainWindow::on_G3_Ck_stateChanged(int arg1) { this->generalGroupSelect(2,arg1); }

void MainWindow::on_G4_Ck_stateChanged(int arg1) { this->generalGroupSelect(3,arg1); }

void MainWindow::on_G5_Ck_stateChanged(int arg1) { this->generalGroupSelect(4,arg1); }

void MainWindow::on_G6_Ck_stateChanged(int arg1) { this->generalGroupSelect(5,arg1); }

void MainWindow::on_G7_Ck_stateChanged(int arg1) { this->generalGroupSelect(6,arg1); }

void MainWindow::on_G8_Ck_stateChanged(int arg1) { this->generalGroupSelect(7,arg1); }

void MainWindow::on_G9_Ck_stateChanged(int arg1) { this->generalGroupSelect(8,arg1); }

void MainWindow::on_G10_Ck_stateChanged(int arg1) { this->generalGroupSelect(9,arg1); }

void MainWindow::signatureSelect(int index, int arg){
    if(arg == 0){
        whoSigns_[index] = 0;
        signatureCounter_--;
    }
    else {
        whoSigns_[index] = 1;
        signatureCounter_++;
    }

    //print out current config
    for (int i = 0;i<5;i++) {
        cout << whoSigns_[i] << "  ";
        if(i == 4){
            cout << endl;
        }
    }

        //cap the signings at 2 people. Disable the buttons otherwise
        if(signatureCounter_ >= 2){
            int tempCounter = 0;
            for(int i = 0; i < 5; i++){
                if(whoSigns_[i] == 0) {
                    if(tempCounter == 0)
                        ui->toSign1->setEnabled(false);
                    else if(tempCounter == 1)
                        ui->toSign2->setEnabled(false);
                    else if(tempCounter == 2)
                        ui->toSign3->setEnabled(false);
                    else if(tempCounter == 3)
                        ui->toSign4->setEnabled(false);
                    else if(tempCounter == 4)
                        ui->toSign5->setEnabled(false);
                    }
                tempCounter += 1;
            }
            tempCounter = 1;
        }
        else {
            ui->toSign1->setEnabled(true);
            ui->toSign2->setEnabled(true);
            ui->toSign3->setEnabled(true);
            ui->toSign4->setEnabled(true);
            ui->toSign5->setEnabled(true);
        }

        isItGeneratable();
}

void MainWindow::on_toSign1_stateChanged(int arg1) { this->signatureSelect(0,arg1); }

void MainWindow::on_toSign2_stateChanged(int arg1) { this->signatureSelect(1,arg1); }

void MainWindow::on_toSign3_stateChanged(int arg1) { this->signatureSelect(2,arg1); }

void MainWindow::on_toSign4_stateChanged(int arg1) { this->signatureSelect(3,arg1); }

void MainWindow::on_toSign5_stateChanged(int arg1) { this->signatureSelect(4,arg1); }

void MainWindow::enableEventSettings(){
    if(eventSelected_ == 0)
        ui->eventSetting->setEnabled(false);
    else {
        ui->eventSetting->setEnabled(true);
    }
}

void MainWindow::on_eventSetting_clicked()
{
    //recording eventSelected setting on a temporary file
    ofstream writeFile(my_workingdir() + "/data/intermediate/A_to_B.txt", std::ofstream::out | std::ofstream::trunc);
    if(!writeFile) { cerr << "Main to eventSettings file failed to be created.\n"; }
    writeFile << eventSelected_;
    writeFile.close();

    //Actually opening the window
    eventSettings myWindow;
    myWindow.setModal(true);
    myWindow.exec();
}

void MainWindow::on_aboutBtn_clicked()
{
    About myWindows;
    myWindows.setModal(false);
    myWindows.exec();
}

void MainWindow::on_instructionsBtn_clicked()
{
    //system("start .\\data\\other\\README.html");
    showSamplePDF("/data/other/README.html");
}

void MainWindow::on_viewTemplateBtn_clicked()
{
    if(eventSelected_ == 1){
        showSamplePDF("/data/templates/StiFe/Sample.pdf");
    }
    else if(eventSelected_ == 2){
        showSamplePDF("/data/templates/Thomastag/Sample.pdf");
    }
    else if(eventSelected_ == 3){
        showSamplePDF("/data/templates/SemPro/Sample.pdf");
    }
    else if(eventSelected_ == 4){
        showSamplePDF("/data/templates/Saugrillen/Sample.pdf");
    }
}

void MainWindow::isItGeneratable(){

    int groupsChosen = 0;
    for(size_t i = 0; i < groupsChosen_.size(); i++){
        if(groupsChosen_[i] == 1)
            groupsChosen++;
    }

    if((eventSelected_ != 0) && (signatureCounter_ != 0) &&
            (groupsChosen != 0)){
        PDFgeneratable = true;
    } else {
        PDFgeneratable = false;
    }

    if(PDFgeneratable)
        ui->generateBtn->setEnabled(true);
    else
        ui->generateBtn->setEnabled(false);
}

void MainWindow::makeList(std::ifstream &file){
    _groupsProcessed++;

    std::string title,fName,lName,job_position,street,zip,land,anrede = "";
    std::string greetLine = "";
    std::string forw_add = ""; //the address that will be visible on the letter

    char delimiter = '$';

    if(_groupsProcessed == 1)
        m_fin << "title$anrede$fName$lName$street$zip$land$job_position$greetline$forw_add" << endl;

    int pplProcessed = 0;

    while(true){
        //Break logic at the end of loop

        pplProcessed++;



        std::getline(file,anrede,delimiter);
        std::getline(file,title,delimiter);
        std::getline(file,lName,delimiter);
        std::getline(file,fName,delimiter);
        std::getline(file,street,delimiter);
        std::getline(file,zip,delimiter);
        std::getline(file,land,delimiter);
        std::getline(file,job_position,'\n');


        if(pplProcessed == 1) { continue; }

        //composing finalList




        m_fin << title << "$" << anrede << "$" << fName << "$" << lName << "$" << street << "$" << zip
              << "$" << land << "$" << job_position << "$";


        if(anrede == "Frau"){
            if(title == "")
                m_fin << "Sehr geehrte " << anrede << " " << lName <<  ",";
            else
                m_fin << "Sehr geehrte " << title << " " << lName <<  ",";
        }
        else {
            if(title == "")
                m_fin << "Sehr geehrter " << anrede << " " << lName <<  ",";
            else
                m_fin << "Sehr geehrter " << title << " " << lName <<  ",";
        }


        m_fin << "$" << fName << " " << lName << " \\\\ " << street << " \\\\ " << zip;
        if(land != "DE"){
            m_fin << " \\\\ " << land;
        }
        m_fin << endl;


        //BREAK LOGIC here
        if(file.eof()){
            break;
        }

    } //END of while loop

}

void MainWindow::on_generateBtn_clicked()
{
    cout << "Starting to generate PDF.\n";
    ui->generateBtn->setAutoFillBackground(true);
    ui->generateBtn->setStyleSheet("background-color:rgb(52, 235, 198)");
    ui->generateBtn->setText("Generating PDF");

    //creating a final file with all the personally unique info

    m_fin.open(my_workingdir() + "/data/finalList.tex");
    if(!m_fin) { cerr << "Final guest list failed to generate.\n";}

    for (size_t i = 0;i < groupsChosen_.size();i++) {
        if(groupsChosen_[i] == 1){
            if(i == 8){
                std::ifstream tempRead(my_workingdir() + "/data/datenbank/G9.csv"); //for reading every individual group csv file
                makeList(tempRead);

            } else if (i == 9){
                std::ifstream tempRead(my_workingdir() + "/data/datenbank/G10.csv"); //for reading every individual group csv file
                makeList(tempRead);

            } else if (i == 4){
                std::ifstream tempRead(my_workingdir() + "/data/datenbank/G5.csv"); //for reading every individual group csv file
                makeList(tempRead);

            } else if (i == 0){
                std::ifstream tempRead(my_workingdir() + "/data/datenbank/G1.csv"); //for reading every individual group csv file
                makeList(tempRead);

            } else if (i == 1){
                std::ifstream tempRead(my_workingdir() + "/data/datenbank/G2.csv");
                makeList(tempRead);

            } else if (i == 2){
                std::ifstream tempRead(my_workingdir() + "/data/datenbank/G3.csv"); //for reading every individual group csv file
                makeList(tempRead);

            } else if (i == 3){
                std::ifstream tempRead(my_workingdir() + "/data/datenbank/G4.csv"); //for reading every individual group csv file
                makeList(tempRead);

            } else if (i == 5){
                std::ifstream tempRead(my_workingdir() + "/data/datenbank/G6.csv"); //for reading every individual group csv file
                makeList(tempRead);

            } else if (i == 6){
                std::ifstream tempRead(my_workingdir() + "/data/datenbank/G7.csv"); //for reading every individual group csv file
                makeList(tempRead);

            } else if (i == 7){
                std::ifstream tempRead(my_workingdir() + "/data/datenbank/G8.csv"); //for reading every individual group csv file
                makeList(tempRead);

            }
        } //end of main if-statement
        else{
            cout << "Group " << i + 1 << " not selected. Moving to next group.\n";
        }
    } // end of for loop


    ui->generateBtn->setText("Participant list created");

    //Making final PDF latex file

    ifstream m_fin2(my_workingdir() + "/data/finalList.tex");
    if(!m_fin) { cerr << "finalList file failed to open.\n";}

    ofstream m_res(my_workingdir() + "/data/FINAL.tex");
    if(!m_res) { cerr << "ResultPDF file failed to open.\n";}


    string token;

    char delim = '$';
    int counter = 0; //The counter for differentiating each token
    string title,fName,lName,job_position,street,zip,land,anrede,forw_add;
    string greetLine;

    int yearOfEvent;
    time_t current = time(0);
    tm *local_time = localtime(&current);
    yearOfEvent = 1900 + local_time->tm_year - 1921; //a nice utility variable

    string semesterJahr = "nothing yet";
    int base = 1900 + local_time->tm_year-2000; // if current year is 2020, base = 20

    if(local_time->tm_mon >= 1 && local_time->tm_mon < 7){
        semesterJahr = "Q1 / ";
        semesterJahr += to_string(base);
    } else {
        semesterJahr = "Q2 / ";
        semesterJahr += to_string(base);
    }

    // making the title
    title = "To-be-filled in";
    if(eventSelected_ == 1){
        title = "Invitation to EVENT 1";
    } else if(eventSelected_ == 2) {
        title = "Invitation to EVENT 2";
    } else if(eventSelected_ == 3) {
        title = "Invitation to EVENT 3";
    } else if(eventSelected_ == 4) {
        title = "Invitation to EVENT 4";
    }



    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    m_res << "\\documentclass[" << endl;
    m_res << "\tpagenumber=false," << endl;
    m_res << "\tparskip=half," << endl;
    m_res << "\tfromalign=right," << endl;
    m_res << "\tfoldmarks=true," << endl;
    m_res << "\taddrfield=true" << endl;
    m_res << "]{scrlttr2}" << endl << endl;

    m_res << "\\usepackage[T1]{fontenc}" << endl;
    m_res << "\\usepackage{stix}" << endl << endl;

    m_res << "\\usepackage[english]{babel}" << endl << endl;

    m_res << "\\usepackage{graphicx}" << endl;
    m_res << "\\graphicspath{ {" << "./unterschriften/" << "} }" << endl << endl;
    m_res << "\\usepackage{wrapfig}" << endl << endl;

    m_res << "\\renewcommand*{\\raggedsignature}{\\raggedright}" << endl << endl;

    m_res << "\\setkomavar{fromname}{COMPANY NAME HERE}" << endl << endl;

    m_res << "\\setkomavar{fromaddress}{COMPANY ADDRESS HERE}" << endl << endl;

    m_res << "\\setkomavar{title}{" << title << "}" << endl << endl;

    //redefining today's date format
    m_res << "\\def\\mydate{ \\leavevmode\\hbox{\\twodigits\\day.\\twodigits\\month.\\the\\year} }" << endl;
    m_res << "\\def\\twodigits#1{\\ifnum#1 < 10 0\\fi\\the#1}" << endl << endl;

    m_res << "\\date{COMPANY CITY HERE, \\mydate}" << endl;

    m_res << "\\begin{document}" << endl << endl;


    while(m_fin2.good()){
        counter++;
        std::getline(m_fin2, title, delim);
        std::getline(m_fin2, anrede, delim);
        std::getline(m_fin2, fName, delim);
        std::getline(m_fin2, lName, delim);
        std::getline(m_fin2, street, delim);
        std::getline(m_fin2, zip, delim);
        std::getline(m_fin2, land, delim);
        std::getline(m_fin2, job_position, delim);
        std::getline(m_fin2, greetLine, delim);
        std::getline(m_fin2, forw_add, '\n');

        if (counter == 1) continue;

        m_res << "\\begin{letter}{" << forw_add << "}" << endl;
        m_res << "\\opening{" << greetLine << "}" << endl;

        //main contents here
        m_res << letterContent();

        m_res << endl << "\\vspace{1.5cm}" << endl;

        m_res << "\n\nMit freundlichen Grüßen," << endl << endl;
        m_res << placeSignatures() << endl;
        m_res << "\\end{letter}" << endl << endl << endl;
    }

    m_res << "\\end{document}" << endl;
    m_res.close();
    m_fin.close();
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    cout << counter - 1 << " pages generated.\n";

    // Replacing placeholders with actual data

    string anDatum, enDatum, meldDatum;

    ifstream theEventData(my_workingdir() + "/data/intermediate/B_to_A.txt");
    if(!theEventData) {cerr << "Data can't be obtained from B_to_A file.\n";}

    getline(theEventData,anDatum,'\n');
    getline(theEventData,enDatum,'\n');
    getline(theEventData,meldDatum,'\n');

    cout << "Proof that data was sucessfully collected from B_to_A:\n";
    cout << "anDatum: " << anDatum << endl
         << "enDatum: " << enDatum << endl
         << "meldDatum: " << meldDatum << endl;


    placeholder_replace(to_string(yearOfEvent),anDatum,enDatum,meldDatum);

}

void MainWindow::placeholder_replace(std::string stiFe,std::string anDatum, std::string enDatum, std::string meldDatum) {

    string data[4] = {stiFe,anDatum,enDatum,meldDatum};
    string reference[4] = {"<yearOfEvent>","<anDatum>","<enDatum>","<meldDatum>"};

    for(int i = 0; i < 4; i++){
        ifstream m_rep(my_workingdir() + "/data/FINAL.tex");
        if(!m_rep) { cerr << "finalPDF (iteration " << i << " ) file failed to open.\n";}

        stringstream buffer;
        buffer << m_rep.rdbuf();

        string total = buffer.str();
        string replace = reference[i];

        std::size_t pos = 2;
        while (pos != std::string::npos) {
            //Find 'replace'
            pos = total.find(replace);

            //If it found 'replace', replace it with "night"
            if (pos != std::string::npos)
                total.replace(pos, replace.length(), data[i]);
        }

        m_rep.close();

        ofstream m_rep2(my_workingdir() + "/data/finalPDF.tex");
        if(!m_rep2) { cerr << "finalPDF (iteration " << i << " {during replacing} ) file failed to open.\n";}

        m_rep2 << total;
        m_rep2.close();
    }
    cout << "Data replacement sequence complete.\n";
}

string MainWindow::letterContent(){
    //1: Event 1 ; 2: Event 2 ; 3: Event 3 ; 4: Event 4
    ifstream readFile, extraReadFile;
    string templateData;
    if(eventSelected_ == 1){ //StiFe
        readFile.open(my_workingdir() + "/data/templates/Event1/edit_me.txt");
        if(!readFile) {ui->generateBtn->setText("Event 1 template error!");}

        stringstream buffer;
        buffer << readFile.rdbuf();

        extraReadFile.open(my_workingdir() + "/data/intermediate/actual_template.txt");
        if(!extraReadFile) {ui->generateBtn->setText("user-input template error!");}

        buffer << extraReadFile.rdbuf();

        templateData = buffer.str();
        return templateData;

    } else if(eventSelected_ == 2){
        readFile.open(my_workingdir() + "/data/templates/Event2/edit_me.txt");
        if(!readFile) {ui->generateBtn->setText("Event 2 template error!");}
    } else if(eventSelected_ == 3){
        readFile.open(my_workingdir() + "/data/templates/Event3/edit_me.txt");
        if(!readFile) {ui->generateBtn->setText("Event 3 template error!");}
    } else if(eventSelected_ == 4){
        readFile.open(my_workingdir() + "/data/templates/Event4/edit_me.txt");
        if(!readFile) {ui->generateBtn->setText("Event 4 template error!");}
    }

    stringstream buffer;
    buffer << readFile.rdbuf();

    readFile.close();
    return buffer.str();
}

string MainWindow::placeSignatures(){
    string returnValue = "";

    ifstream temp(my_workingdir() + "/data/intermediate/sigNames.txt");
    if(!temp) { cerr << "File to store full signature names failed to open.\n"; }

    string amt;
    int signedPerson = -1;

    string p1, p2 , p3, p4, p5;
    getline(temp,p1,'\n');
    getline(temp,p2,'\n');
    getline(temp,p3,'\n');
    getline(temp,p4,'\n');
    getline(temp,p5,'\n');



    string sig1, text1, sig2, text2;
    string fieldArray[4] = {sig1, text1, sig2, text2};
    if(signatureCounter_ == 1){
        sig2 = "";
        text2 = "";

        for(auto i = 0; i < whoSigns_.size(); i++){
            if(whoSigns_[i] != 0 && i != signedPerson){

                if(i == 0) {
                    amt = "1";
                    signedPerson = i;
                    text1 = p1;
                } else if(i == 1){
                    amt = "2";
                    signedPerson = i;
                    text1 = p2;
                } else if(i == 2){
                    amt = "3";
                    signedPerson = i;
                    text1 = p3;
                } else if(i == 3){
                    amt = "4";
                    signedPerson = i;
                    text1 = p4;
                } else if(i == 4){
                    amt = "5";
                    signedPerson = i;
                    text1 = p5;
                }

                sig1 = "\\includegraphics[scale=0.3]{" + amt + "}";

                signedPerson = i;
                break;
            }
        }
    } else {

        //first signature

        for(auto i = 0; i < whoSigns_.size(); i++){
            if(whoSigns_[i] != 0 && i != signedPerson){

                if(i == 0) {
                    amt = "1";
                    signedPerson = i;
                    text1 = p1;
                } else if(i == 1){
                    amt = "2";
                    signedPerson = i;
                    text1 = p2;
                } else if(i == 2){
                    amt = "3";
                    signedPerson = i;
                    text1 = p3;
                } else if(i == 3){
                    amt = "4";
                    signedPerson = i;
                    text1 = p4;
                } else if(i == 4){
                    amt = "5";
                    signedPerson = i;
                    text1 = p5;
                }

                sig1 = "\\includegraphics[scale=0.3]{" + amt + "}";

                signedPerson = i;
                break;
            }
        }

        //second signature

        for(auto i = 0; i < whoSigns_.size(); i++){
            if(whoSigns_[i] != 0 && i != signedPerson){

                if(i == 0) {
                    amt = "1";
                    signedPerson = i;
                    text1 = p1;
                } else if(i == 1){
                    amt = "2";
                    signedPerson = i;
                    text1 = p2;
                } else if(i == 2){
                    amt = "3";
                    signedPerson = i;
                    text1 = p3;
                } else if(i == 3){
                    amt = "4";
                    signedPerson = i;
                    text1 = p4;
                } else if(i == 4){
                    amt = "5";
                    signedPerson = i;
                    text1 = p5;
                }

                sig1 = "\\includegraphics[scale=0.3]{" + amt + "}";

                signedPerson = i;
                break;
            }
        }
    }


    //sig1 = "1"; text1 = "2";sig2 = "3";text2 = "4";

    returnValue = "\\begin{tabular}{ll}\n";
    returnValue += sig1 + " & " + sig2 + " \\\\\n";
    returnValue += text1 + " & " + text2 + " \\\\\n";
    returnValue += "\\end{tabular}\n";

    return returnValue;
}
