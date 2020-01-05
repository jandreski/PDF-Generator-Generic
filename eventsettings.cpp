#include "eventsettings.h"
#include "ui_eventsettings.h"
#include "mainwindow.h"

#include <iostream>
#include <string>
#include <QMessageBox>
#include <QTextStream>

#include "utility.h"

using namespace std;

eventSettings::eventSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::eventSettings)
{
    ui->setupUi(this);

    std::ifstream readFile(my_workingdir() + "/data/intermediate/A_to_B.txt");
    if(!readFile) { cerr << "Main to eventSettings file failed to be opened.\n"; }
    stringstream buffer;
    buffer << readFile.rdbuf();
    _readEventSelected = stoi(buffer.str()); //stoi converts string to int

    //What to enable, based on the inputs
    if(_readEventSelected == 1){ // Event 1
        ui->beginDate->setEnabled(true);
        ui->endDate->setEnabled(true);
        ui->signUpDate->setEnabled(false);
        ui->unlockScheduleMaker->setEnabled(true);
    }
    else if(_readEventSelected == 2){ // Event 2
        ui->beginDate->setEnabled(true);
        ui->endDate->setEnabled(true);
        ui->signUpDate->setEnabled(true);
        ui->unlockScheduleMaker->setEnabled(false);
    }
    else if(_readEventSelected == 3){ // Event 3
        ui->beginDate->setEnabled(false);
        ui->endDate->setEnabled(false);
        ui->signUpDate->setEnabled(false);
        ui->unlockScheduleMaker->setEnabled(false);
    }
    else if(_readEventSelected == 4){ // Event 4
        ui->beginDate->setEnabled(true);
        ui->endDate->setEnabled(false);
        ui->signUpDate->setEnabled(false);
        ui->unlockScheduleMaker->setEnabled(false);
    } else
        cout << "How did you do this buddy?" << " We're on event " << _readEventSelected << endl;
}

eventSettings::~eventSettings()
{
    delete ui;
}

void eventSettings::on_buttonBox_accepted()
{
    std::ofstream writeFile(my_workingdir() + "/data/intermediate/B_to_A.txt");
    if(!writeFile) { cerr << "eventSetting to Main intermediate file failed to be created.\n"; }

    _anDatum = ui->beginDate->text().toUtf8().constData();
    _enDatum = ui->endDate->text().toUtf8().constData();
    _meldDatum = ui->signUpDate->text().toUtf8().constData();

    writeFile << _anDatum << endl
              << _enDatum << endl
              << _meldDatum << endl;
    writeFile.close();
}

void eventSettings::on_unlockScheduleMaker_clicked()
{
    ui->updateSchedule->setEnabled(true);
    ui->scheduleMaker->setEnabled(true);
    ui->unlockScheduleMaker->deleteLater();
    QString directory = QString::fromStdString(my_workingdir()) + "\\data\\intermediate\\schedule_template.txt";
    //cout << directory.toUtf8().constData() << endl;
    QFile readFile(directory);

    if(!readFile.open(QFile::ReadOnly | QFile::Text)){

        cout << "ERROR: File failed to open\n";
        QMessageBox messageBox;
        messageBox.critical(this,"Error","Template not found. Consult the instructions.");
        messageBox.setFixedSize(500,200);
    }

    QTextStream in(&readFile);
    in.setCodec("UTF-8");
    in.setGenerateByteOrderMark(true);

    ui->scheduleMaker->document()->setPlainText(in.readAll());
}

void eventSettings::on_updateSchedule_clicked()
{
    QString directory = QString::fromStdString(my_workingdir()) + "\\data\\intermediate\\actual_template.txt";
    QFile writeFile(directory);

    if(!writeFile.open(QFile::WriteOnly | QFile::Text)){

        cout << "ERROR: File failed to open\n";
        QMessageBox messageBox;
        messageBox.critical(this,"Error","Placeholder file not found. Consult the instructions.");
        messageBox.setFixedSize(500,200);
    }

    QTextStream out(&writeFile);
    out.setCodec("UTF-8");
    out.setGenerateByteOrderMark(true);

    out << ui->scheduleMaker->toPlainText();
    writeFile.close();

}
