#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "gamers.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    QString getLogin();
    QString getPass();



signals:
    void login_button_clicked();
    void register_button_clicked();

private slots:
    void on_buttonStart_clicked();

    void on_buttonGetRole_clicked();

    void on_buttonGetRoleCancel_clicked();

    void on_lineEditName_textEdited(const QString &arg1);

    void on_lineEditPassword_textEdited(const QString &arg1);

    void on_buttonRegister_clicked();

private:
    Ui::Login *ui;
    QString m_username;
    QString m_userpass;
    Gamer *gamer;
};

#endif // LOGIN_H
