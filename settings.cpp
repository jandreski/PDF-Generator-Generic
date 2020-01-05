#include "settings.h"
#include "ui_settings.h"
#include <QFile>
#include <iostream>
#include <string>
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>

//#include <locale>
//#include <codecvt>

#include <windows.h>
#include "utility.h"

using namespace std;

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    //My inputs

    //displaying the current data
    displayCurrentConfig();
}

Settings::~Settings()
{
    delete ui;
}

void Settings::displayCurrentConfig(){

    //string fileDir = GetCurrentWorkingDir() + "/data/config.csv";
    string fileDir = my_workingdir() + "\\data\\config.csv";
    QFile readFile(QString::fromStdString(fileDir));
//    QFile readFile("C:/Users/jakov/Documents/qtProper/mailingSystemCPP/data/config.csv");
    if(!readFile.open(QFile::ReadOnly | QFile::Text)){

        cout << "ERROR: File failed to open\n";
        QMessageBox messageBox;
        messageBox.critical(this,"Error","Configuration file failed to open. Program will exit.");
        messageBox.setFixedSize(500,200);
        exit(EXIT_FAILURE);
    }

    QTextStream in(&readFile);
    in.setCodec("UTF-8");
    in.setGenerateByteOrderMark(true);

    cout << "Current Directory is: " << my_workingdir() << endl;

    QString amt,fName,lName,job_position;
    //readFile.seekg(30);

    int tempCounter = 0;
    while(!in.atEnd()){
        tempCounter++;
        //string lineInput = static_cast<string>(readFile.readLine());
        //QString lineInput = QString::fromUtf8(readFile.readLine());
        QString lineInput = in.readLine();


        //extracting data from the string,and assigning it to the proper variables
        int c2 = 0; //counter 2

        //string delimiter = ",";
        QString delimiter = ",";

        int pos = 0;
        QString token;
        //string token;
        while (true) {
            c2++;
            //determining what delimiter the program needs to look, based on how far it is in the string
            if(c2 == 4)
                pos = lineInput.indexOf("\n");
                //pos = lineInput.find("\n");
            else
                pos = lineInput.indexOf(delimiter);
                //pos = lineInput.find(delimiter);
            //taking a substring from the main string, using the position 'pos' obtained above
            token = lineInput.mid(0,pos);
            //assigning the 'token' accordingly
            if(c2 == 1)
                amt = token;
            else if(c2 == 2)
                fName = token;
            else if(c2 == 3)
                lName = token;
            else if(c2 == 4){
                job_position = token;
                c2 = 0;
                break;
            }
            //deleting parts of the string when they're not necessary
            lineInput.remove(0,pos + delimiter.length());
            //lineInput.erase(0, pos + delimiter.length());
        }

        //displaying data on the UI
        if(tempCounter == 1){
            ui->vN1->setText(fName); //converts from string to QString
            ui->nN1->setText(lName);
            ui->bs1->setText(job_position);
        }
        else if (tempCounter == 2){
            ui->vN2->setText(fName); //converts from string to QString
            ui->nN2->setText(lName);
            ui->bs2->setText(job_position);
        }
        else if (tempCounter == 3){
            ui->vN3->setText(fName); //converts from string to QString
            ui->nN3->setText(lName);
            ui->bs3->setText(job_position);
        }
        else if (tempCounter == 4){
            ui->vN4->setText(fName); //converts from string to QString
            ui->nN4->setText(lName);
            ui->bs4->setText(job_position);
        }
        else if (tempCounter == 5){
            ui->vN5->setText(fName); //converts from string to QString
            ui->nN5->setText(lName);
            ui->bs5->setText(job_position);
            tempCounter = 0;
            break;
        }

      }
    readFile.flush();
    readFile.close();
}

void Settings::updateConfig(){
    string fileDir = my_workingdir() + "\\data\\config.csv";
    QFile writeFile(QString::fromStdString(fileDir));
    if(!writeFile.open(QFile::WriteOnly | QFile::Text)){

        cout << "ERROR: File failed to open\n";
        QMessageBox messageBox;
        messageBox.critical(this,"Error","Configuration file failed to open.");
        messageBox.setFixedSize(500,200);
        //exit(EXIT_FAILURE);
    } else{
        cout << "File ready to be rewritten!\n";
        QTextStream out(&writeFile);
        out.setCodec("UTF-8");
        out.setGenerateByteOrderMark(true);
        out << "P1,"<< ui->vN1->text() << "," << ui->nN1->text() << "," << ui->bs1->text() << endl
            << "P2,"<< ui->vN2->text() << "," << ui->nN2->text() << "," << ui->bs2->text() << endl
            << "P3,"<< ui->vN3->text() << "," << ui->nN3->text() << "," << ui->bs3->text() << endl
            << "P4,"<< ui->vN4->text() << "," << ui->nN4->text() << "," << ui->bs4->text() << endl
            << "P5,"<< ui->vN5->text() << "," << ui->nN5->text() << "," << ui->bs5->text() << endl;

        //updatePreviewBox(MainWindow::getUi());



        //creating new tempfile to store full chargia names
        ofstream temp(my_workingdir() + "/data/intermediate/sigNames.txt");
        if(!temp) { cerr << "File to store full chargia names failed to create.\n"; }

        temp << ui->vN1->text().toUtf8().constData() << " " << ui->nN1->text().toUtf8().constData();
        if(ui->bs1->text() != "") { temp << " (" << ui->bs1->text().toUtf8().constData() << ")"; }
        temp << endl;

        temp << ui->vN2->text().toUtf8().constData() << " " << ui->nN2->text().toUtf8().constData();
        if(ui->bs2->text() != "") { temp << " (" << ui->bs2->text().toUtf8().constData() << ")"; }
        temp << endl;

        temp << ui->vN3->text().toUtf8().constData() << " " << ui->nN3->text().toUtf8().constData();
        if(ui->bs3->text() != "") { temp << " (" << ui->bs3->text().toUtf8().constData() << ")"; }
        temp << endl;

        temp << ui->vN4->text().toUtf8().constData() << " " << ui->nN4->text().toUtf8().constData();
        if(ui->bs4->text() != "") { temp << " (" << ui->bs4->text().toUtf8().constData() << ")"; }
        temp << endl;


        temp << ui->vN5->text().toUtf8().constData() << " " << ui->nN5->text().toUtf8().constData();
        if(ui->bs5->text() != "") { temp << " (" << ui->bs5->text().toUtf8().constData() << ")"; }
        temp << endl;

        temp.close();
    }
}

void Settings::on_buttonBox_accepted() { updateConfig(); }

void Settings::on_unt1_clicked()
{
    signatureImgs(ui,"1",QFileDialog::getOpenFileName(this, tr("Choose signature:"),"",tr("Images (*.png)")));
}

void Settings::on_unt2_clicked()
{
    signatureImgs(ui,"2",QFileDialog::getOpenFileName(this, tr("Choose signature:"),"",tr("Images (*.png)")));
}

void Settings::on_unt3_clicked()
{
    signatureImgs(ui,"3",QFileDialog::getOpenFileName(this, tr("Choose signature:"),"",tr("Images (*.png)")));
}

void Settings::on_unt4_clicked()
{
    signatureImgs(ui,"4",QFileDialog::getOpenFileName(this, tr("Choose signature:"),"",tr("Images (*.png)")));
}

void Settings::on_unt5_clicked()
{
    signatureImgs(ui,"5",QFileDialog::getOpenFileName(this, tr("Choose signature:"),"",tr("Images (*.png)")));
}
