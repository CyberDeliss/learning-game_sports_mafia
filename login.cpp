#include "day.h"
#include "login.h"
#include "ui_login.h"
#include "gamers.h"
#include <QApplication>

Gamer *gamer = nullptr;

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

enum loginResult {
    SUCCESS = 0,
    ERROR_LENGHT_NAME = -1, //слишком длинное имя пользователя
    ERROR_NEED_NAME = -2, // нужно заполнить имя
};

loginResult readLogin(QString m_login){
    if (m_login.length() > 10)
        return ERROR_LENGHT_NAME;
    if (m_login == "")
        return ERROR_NEED_NAME;
    return SUCCESS; // если всё прошло успешно
}

Id getRandomId(){
    srand( time(0) );
    int m_random = 1 + rand() % 10 ;
    return Id(m_random);
}

Role getRandomRole(){
    srand( time(0) );
    int m_random = 1 + rand() % 4 ;
    return Role(m_random);
}


void Login::on_buttonStart_clicked()
{
//    int m_intRole = ui->label_role->text().toInt();


    QWidget *day = new Day();
    day->show();
    this->close();
}

QString printRole(Role role){
    switch (role)
    {
    case Role::RED:
        return "Мирный житель";
        break;
    case Role::POLICMAN:
        return "Комиссар";
        break;
    case Role::DON:
        return "Дон мафии";
        break;
    case Role::MAFIA:
        return "Мафия";
        break;
    default:
        return "Ваша роль:";
        break;
    }
}

Gamer *getStructGamer(Id id, Role role, QString name) {
    switch (role)    {
    case Role::RED:
        return new Gamer(id, role, name);
        break;
    case Role::POLICMAN:
        return new Policman(id, role, name);
        break;
    case Role::MAFIA:
        return new  Mafia(id, role, name);
        break;
    case Role::DON:
        return new  Don(id, role, name);
        break;
    }
}


void Login::on_buttonGetRole_clicked(){

    QString m_myName = ui->lineEditName->text();

    if (readLogin(ui->lineEditName->text()) == SUCCESS)
    {
        Role m_myRole = getRandomRole(); //TODO в будущем реализовать нормальную раздачу ролей игрокам.
        Id m_myId = getRandomId();       //TODO в будущем реализовать нормальную раздачу ID игрокам.

        if (m_myId != ZERO){
            if (!gamer){
                gamer= getStructGamer(m_myId, m_myRole, m_myName);

            }else{
                delete gamer;
                gamer= getStructGamer(m_myId, m_myRole, m_myName);
            }
         }

        ui->lineEditName->setEnabled(false);
        ui->buttonStart->setEnabled(true);
        ui->label_role->setText(printRole(m_myRole));
        ui->label_id->setText(QString::number(m_myId));
    }
    else{
        ui->label_3->setText("Не корректно");
    }
}

void Login::on_buttonGetRoleCancel_clicked()
{
    delete gamer;       //освобождение памяти по адресу
    gamer = nullptr;    //обнуление адреса

    ui->label_3->setText("");
    ui->buttonStart->setEnabled(false);
    ui->lineEditName->setEnabled(true);
    ui->label_role->setText("Ваша роль:");
    ui->label_id->setText("Ваш номер:");
}
