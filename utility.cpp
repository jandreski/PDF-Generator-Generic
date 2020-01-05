#include "utility.h"

#include <string>
#include <vector>
#include <QString>
#include <windows.h>
#include <iostream>
#include <QFile>
#include <QPixmap>
#include <QTextStream>
#include <QDesktopServices>

#include "settings.h"
#include "ui_settings.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

std::string my_workingdir()
{
    char buf[256];
    GetCurrentDirectoryA(256, buf);
    return string(buf);
}

std::string conv_fDash(std::string input){
    string result = "";
    for (size_t i = 0;i < input.length();i++) {
        if(input[i] == '/'){
            result += "\\";
        } else{
            result += input[i];
        }
    }
    return result;
}

void signatureImgs(Ui::Settings *ui,std::string posToAlter, QString originalImgPath){
    if(originalImgPath != ""){
        cout << "Original Image path: " << conv_fDash(originalImgPath.toStdString()) << endl;

        QPixmap toShow(originalImgPath);
        ui->previewSignatureBox->setPixmap(toShow.scaled(350,75));

        string in1 = "del .\\data\\unterschriften\\"+ posToAlter + ".png";
        char p2[in1.length()];
            for (auto i = 0; i < sizeof(p2); i++)
                p2[i] = in1[i];
        system(p2);

        string cmd_input = "copy \"" + originalImgPath.toStdString() + "\" " + "\"./data/unterschriften/" + posToAlter + ".png\"";
        cmd_input = conv_fDash(cmd_input);
        char p[cmd_input.length()];
            for (auto i = 0; i < sizeof(p); i++)
                p[i] = cmd_input[i];
        system(p);
    }
}

void updatePreviewBox(Ui::MainWindow *ui){
    if(!generateBtnPressed){
        QString preGenerateOutput = "Current configuration:\n";

        string fileDir = my_workingdir() + "\\data\\config.csv";
        QFile readFile(QString::fromStdString(fileDir));

        if(!readFile.open(QFile::ReadOnly | QFile::Text)) { //fail-safe

            cout << "ERROR: File failed to open\n";
            exit(EXIT_FAILURE);
        }

        QTextStream in(&readFile);
        in.setCodec("UTF-8");
        in.setGenerateByteOrderMark(true);

        QString amt,fName,lName,job_position;

        int tempCounter = 0;
        while(!in.atEnd()){
            tempCounter++;
            QString lineInput = in.readLine();

            //extracting data from the string,and assigning it to the proper variables
            int c2 = 0; //counter 2

            QString delimiter = ",";

            int pos = 0;
            QString token;
            while (true) {
                c2++;
                //determining what delimiter the program needs to look, based on how far it is in the string
                if(c2 == 4)
                    pos = lineInput.indexOf("\n");
                    //pos = lineInput.find("\n");
                else
                    pos = lineInput.indexOf(delimiter);

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
                    preGenerateOutput += amt + ": " + fName + " " + lName + "  (" + job_position + ")\n";
                    break;
                }
                lineInput.remove(0,pos + delimiter.length());
            }

          }

        readFile.flush();
        readFile.close();

        //output to the text field
        ui->currConfigBox->setText(preGenerateOutput);
    } else {
        //post-generation data
    }
}

void showSamplePDF(std::string pathToSample){
    std::string a = "file:///" + my_workingdir() + pathToSample;
    QString a2 = QString::fromStdString(a);
    QDesktopServices::openUrl(QUrl(a2, QUrl::TolerantMode));
}
