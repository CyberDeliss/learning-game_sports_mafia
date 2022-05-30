#include "reg_window.h"
#include "ui_reg_window.h"

reg_window::reg_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reg_window)
{
    ui->setupUi(this);
}

reg_window::~reg_window()
{
    delete ui;
}

void reg_window::on_lineEditName_textEdited(const QString &arg1)
{
    reg_window::m_userName = arg1;
}


void reg_window::on_lineEditPassword_textEdited(const QString &arg1)
{
    reg_window::m_userPass = arg1;
    if (reg_window::m_userPass == reg_window::m_confirmation){
        ui->buttonRegister->setEnabled(true) ;
    }else{
        ui->buttonRegister->setEnabled(false) ;
    }
}


void reg_window::on_lineEditConfirm_textEdited(const QString &arg1)
{
    reg_window::m_confirmation = arg1;
    if (reg_window::m_userPass == reg_window::m_confirmation){
        ui->buttonRegister->setEnabled(true) ;
    }else{
        ui->buttonRegister->setEnabled(false) ;
    }
}


void reg_window::on_buttonRegister_clicked()
{
    emit register_button_clicked2();
}

void reg_window::on_buttonBack_clicked()
{
    emit back_button_clicked();
}

QString reg_window::getName() { return m_userName; }

QString reg_window::getPass() { return m_userPass; }

bool reg_window::checkPass() { return (m_confirmation == m_userPass); }
