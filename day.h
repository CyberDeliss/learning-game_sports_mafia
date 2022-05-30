#ifndef DAY_H
#define DAY_H

#include <QMainWindow>
#include <QString>
#include <QtSql/QtSql>
#include "login.h"
#include "reg_window.h"
#include "gamers.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Day; }
QT_END_NAMESPACE

class Day : public QMainWindow
{
    Q_OBJECT


public:
    explicit Day(QWidget *parent = nullptr);
    ~Day();
    void display();     // прототип пользовательской функции отображения
    bool connectDB();   // прототип метода подключения к БД


private slots:

    void on_buttonVote_clicked();
    void on_buttonCancel_clicked();
    void authorizeUser();           // пользовательские слоты
    void registerWindowShow();
    void registerUser();
    void backFromReg();

private:
    Ui::Day *ui_Main;

    Login ui_Auth;      // экземпляры окна авторизации и окна регистрации
    reg_window ui_Reg;  // принадлежат главному окну

    QString m_username; // строки для обработки
    QString m_userpass; // пользовательского ввода

    QString db_input;   // строка для отправки запроса к БД

    QSqlDatabase mw_db; // экземпляр подключения к БД

    int user_counter;   // счетчик пользователей
    bool m_loginSuccesfull; // флаг успешной авторизации
};
#endif // DAY_H
