#include "day.h"
#include "login.h"
#include "ui_login.h"
#include "gamers.h"
#include <QApplication>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_buttonStart_clicked()
{
    QWidget *day = new Day();
    day->show();

    this->close();


}


void Login::on_buttonGetRole_clicked()
{
    QString m_myName = ui->lineEditName->text();

    if (m_myName != "") {
       if(m_myName.length() <=10){

           ui->lineEditName->setEnabled(false);
           ui->buttonStart->setEnabled(true);

       }else{
           ui->label_3->setText("Error 2 (name)");
           //слишком длинное имя пользователя
       }
    }else {
        ui->label_3->setText("Error 1 (name)");
        // нужно заполнить имя
    }

}


void Login::on_buttonGetRoleCancel_clicked()
{
    ui->label_3->setText("");
    ui->buttonStart->setEnabled(false);
    ui->lineEditName->setEnabled(true);
}

int getRandomNumber(){

}

int getRandomRole(){

}
