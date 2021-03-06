#include "day.h"
#include "ui_day.h"

Day::Day(QWidget *parent)
    : QMainWindow(parent)
    , ui_Main(new Ui::Day)
{
    user_counter = 0;
    m_loginSuccesfull = false;

    for(int i =0;i<10;i++){
        m_gamer[i] = nullptr;    //обнуление адреса
    }

    QString userpass = "";


        connect(&ui_Auth, SIGNAL(login_button_clicked()),
                this, SLOT(authorizeUser()));
        connect(&ui_Auth,SIGNAL(destroyed()),
                this, SLOT(show()));
        connect(&ui_Reg,SIGNAL(back_button_clicked()),
                this, SLOT(backFromReg()));
        connect(&ui_Auth,SIGNAL(register_button_clicked()),
                this,SLOT(registerWindowShow()));
        connect(&ui_Reg,SIGNAL(register_button_clicked2()),
                this,SLOT(registerUser()));
        connect(&ui_Reg,SIGNAL(destroyed()),
                &ui_Auth, SLOT(show()));


    if(!connectDB())
       {
           qDebug() << "Failed to connect DB";
       }

    QSqlQuery query;

    // userlist(number, name, pass, winr, winb)"
    db_input = "CREATE TABLE userlist ( "
               "number INTEGER PRIMARY KEY NOT NULL,"
               "name VARCHAR(20), "     // увеличить до 20 символов name
               "pass VARCHAR(12), "     // добавить проверку на длину пароля
               "winr INTEGER, "         // побед за красного игрока или комиссара
               "winb INTEGER );" ;      // побед за мафию

    if(!query.exec(db_input))
    {
            qDebug() << "Unable to create a table" << query.lastError();
    }

    ui_Main->setupUi(this);
}


Day::~Day()
{

    if(m_loginSuccesfull)
    {
        QString str_t = "UPDATE userlist "
                        "SET winr = %2, winb = %3 "
                        "WHERE name = '%1';";
        db_input = str_t .arg(m_username)
                         .arg(1)            //сюда передавать данные о победах!
                         .arg(1);
        QSqlQuery query;
        if(!query.exec(db_input))
        {
            qDebug() << "Unable to insert data"  << query.lastError() << " : " << query.lastQuery() ;
        }
    }
    mw_db.removeDatabase("authorisation");
    qDebug() << "MainWindow Destroyed";

    for(int i =0;i<10;i++){
        delete m_gamer[i];       //освобождение памяти по адресу
        m_gamer[i] = nullptr;    //обнуление адреса
    }

    delete ui_Main;
}

void Day::on_buttonVote_clicked()
{


    ui_Main->gamer_1->setFrameShape(QFrame::Panel);
    ui_Main->gamer_2->setFrameShape(QFrame::Panel);
    ui_Main->gamer_3->setFrameShape(QFrame::Panel);
    ui_Main->gamer_4->setFrameShape(QFrame::Panel);
    ui_Main->gamer_5->setFrameShape(QFrame::Panel);
    ui_Main->gamer_6->setFrameShape(QFrame::Panel);
    ui_Main->gamer_7->setFrameShape(QFrame::Panel);
    ui_Main->gamer_8->setFrameShape(QFrame::Panel);
    ui_Main->gamer_9->setFrameShape(QFrame::Panel);
    ui_Main->gamer_10->setFrameShape(QFrame::Panel);

    ui_Main->gamer_1->setFrameShadow(QFrame::Raised);
    ui_Main->gamer_2->setFrameShadow(QFrame::Raised);
    ui_Main->gamer_3->setFrameShadow(QFrame::Raised);
    ui_Main->gamer_4->setFrameShadow(QFrame::Raised);
    ui_Main->gamer_5->setFrameShadow(QFrame::Raised);
    ui_Main->gamer_6->setFrameShadow(QFrame::Raised);
    ui_Main->gamer_7->setFrameShadow(QFrame::Raised);
    ui_Main->gamer_8->setFrameShadow(QFrame::Raised);
    ui_Main->gamer_9->setFrameShadow(QFrame::Raised);
    ui_Main->gamer_10->setFrameShadow(QFrame::Raised);
}

bool Day::connectDB()
{
//  Функция connectDB() устанавливает имя БД и создает соединение с ней. После того, как эта функция будет
//  выполнена впервые, в директории программы появится файл с именем, указанным здесь для базы данных:

    mw_db = QSqlDatabase::addDatabase("QSQLITE");
    mw_db.setDatabaseName("authorisation");
    if(!mw_db.open())
    {
        qDebug() << "Cannot open database: " << mw_db.lastError();
        return false;
    }
    return true;
}

void Day::display()
{
    ui_Auth.show();
}

void Day::on_buttonCancel_clicked()
{
    ui_Main->gamer_1->setFrameShape(QFrame::NoFrame);
    ui_Main->gamer_2->setFrameShape(QFrame::NoFrame);
    ui_Main->gamer_3->setFrameShape(QFrame::NoFrame);
    ui_Main->gamer_4->setFrameShape(QFrame::NoFrame);
    ui_Main->gamer_5->setFrameShape(QFrame::NoFrame);
    ui_Main->gamer_6->setFrameShape(QFrame::NoFrame);
    ui_Main->gamer_7->setFrameShape(QFrame::NoFrame);
    ui_Main->gamer_8->setFrameShape(QFrame::NoFrame);
    ui_Main->gamer_9->setFrameShape(QFrame::NoFrame);
    ui_Main->gamer_10->setFrameShape(QFrame::NoFrame);

}

void Day::registerWindowShow()
{
    ui_Auth.hide();
    ui_Reg.show();
}

void Day::registerUser()
{
    if(ui_Reg.checkPass())
    {
        QSqlQuery query;
        QSqlRecord rec;
        QString str_t = "SELECT COUNT(*) "
                        "FROM userlist;";
        db_input = str_t;
        if(!query.exec(db_input))
        {
            qDebug() << "Unable to get number " << query.lastError() << " : " << query.lastQuery();
            return;
        }
        else
        {
            query.next();
            rec = query.record();
            user_counter = rec.value(0).toInt();
            qDebug() << user_counter;
        }


        m_username = ui_Reg.getName();
        m_userpass = ui_Reg.getPass();
        user_counter++;
        str_t = "INSERT INTO userlist(number, name, pass, winr, winb)"
                "VALUES(%1, '%2', '%3', '%4', '%5');";

        db_input = str_t .arg(user_counter)
                         .arg(m_username)
                         .arg(m_userpass)
                        .arg(0)
                        .arg(0);

        if(!query.exec(db_input))
        {
            qDebug() << "Unable to insert data"  << query.lastError() << " : " << query.lastQuery();
        }
        else
        {
            ui_Reg.hide();
            ui_Auth.show();
        }
    }
    else
    {
        qDebug() << "Confirm password coorectly";
    }

}

void Day::authorizeUser()
{
    int winR = 0;   // побед за мирного игрока или комиссара
    int winB = 0;   // побед за мафию или дона

    m_username = ui_Auth.getLogin();
    m_userpass = ui_Auth.getPass();

    QString str_t = " SELECT * "
                    " FROM userlist "
                    " WHERE name = '%1'";


    QString username = "";
    QString userpass = "";


    db_input = str_t.arg(m_username);

    QSqlQuery query;
    QSqlRecord rec;

    if(!query.exec(db_input))
    {
        qDebug() << "Unable to execute query - exiting" << query.lastError() << " : " << query.lastQuery();
    }

    rec = query.record();
    query.next();
    user_counter = query.value(rec.indexOf("number")).toInt();
    username = query.value(rec.indexOf("name")).toString();
    userpass = query.value(rec.indexOf("pass")).toString();

    if(m_username != username || m_userpass != userpass)
    {
        qDebug() << "Password missmatch" << username << " " << userpass;
        m_loginSuccesfull = false;
    }
    else
    {
        m_loginSuccesfull = true;
        winR = query.value(rec.indexOf("winr")).toInt();
        winB = query.value(rec.indexOf("winb")).toInt();

        m_gamer[ui_Auth.getGamer()->getId()] = ui_Auth.getGamer();
        ui_Auth.close();
        ui_Reg.close();

        ui_Main->labelAboutMe->setText(m_gamer[ui_Auth.getGamer()->getId()]->printAll());
        this->show();

    }
}

void Day::backFromReg(){

    ui_Reg.hide();
    ui_Auth.show();

}
