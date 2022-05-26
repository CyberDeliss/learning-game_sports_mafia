#include "night.h"
#include "ui_night.h"

Night::Night(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Night)
{
    ui->setupUi(this);
}

Night::~Night()
{
    delete ui;
}
