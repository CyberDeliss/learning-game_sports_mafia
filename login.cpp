#include "login.h"
#include "ui_login.h"
#include <QApplication>


Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    m_gamer = nullptr;
    ui->setupUi(this);
}

Login::~Login()
{
    delete m_gamer;       //освобождение памяти по адресу
    m_gamer = nullptr;    //обнуление адреса
    delete ui;
}

enum textResult {
    SUCCESS = 0,
    ERROR_LENGHT_NAME = -1, //слишком длинная строка
    ERROR_NEED_NAME = -2, // пустая строка
};

textResult readText(QString text){
    if (text.length() > 20)
        return ERROR_LENGHT_NAME;
    if (text == "")
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
    emit login_button_clicked();
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

Gamer * Login::getGamer(){
    return m_gamer;
}


void Login::on_buttonGetRole_clicked(){

    QString m_myName = ui->lineEditName->text();

    if (readText(ui->lineEditName->text()) == SUCCESS)
    {
        if (readText(ui->lineEditPassword->text()) == SUCCESS)
        {
            Role m_myRole = getRandomRole(); //TODO в будущем реализовать нормальную раздачу ролей игрокам.
            Id m_myId = getRandomId();       //TODO в будущем реализовать нормальную раздачу ID игрокам.

            if (m_myId != ZERO){
                if (!m_gamer){
                    m_gamer= getStructGamer(m_myId, m_myRole, m_myName);

                }else{
                    delete m_gamer;
                    m_gamer= getStructGamer(m_myId, m_myRole, m_myName);
                }
             }

            ui->lineEditName->setEnabled(false);
            ui->lineEditPassword->setEnabled(false);
            ui->buttonStart->setEnabled(true);
            ui->label_role->setText(printRole(m_myRole));
            ui->label_id->setText(QString::number(m_myId));
        }
        else{
            ui->label_3->setText("Не корректно");
        }
    }
}

void Login::on_buttonGetRoleCancel_clicked()
{
    delete m_gamer;       //освобождение памяти по адресу
    m_gamer = nullptr;    //обнуление адреса

    ui->label_3->setText("");
    ui->buttonStart->setEnabled(false);
    ui->lineEditName->setEnabled(true);
    ui->lineEditPassword->setEnabled(true);
    ui->label_role->setText("role");
    ui->label_id->setText("id");
    ui->lineEditName->setText("");
    ui->lineEditPassword->setText("");
}

void Login::on_lineEditName_textEdited(const QString &arg1)
{
    Login::m_username = arg1;
}


void Login::on_lineEditPassword_textEdited(const QString &arg1)
{
    Login::m_userpass = arg1;
}


QString Login::getLogin() {return m_username;}

QString Login::getPass() {return m_userpass;}


void Login::on_buttonRegister_clicked()
{
    emit register_button_clicked();
}

