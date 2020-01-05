#include "about.h"
#include "ui_about.h"
#include <QPixmap>
#include "windows.h"
#include "utility.h"

using namespace std;

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
}

About::~About()
{
    delete ui;
}
