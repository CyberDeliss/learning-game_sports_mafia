#ifndef GAMERS_H
#define GAMERS_H
#include <QTextStream>

enum class Side{
    RED,
    MAFIA
};

enum class Role {
    RED = 1,
    POLICMAN = 2,
    DON = 3,
    MAFIA = 4
};

enum Id {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN };


class Gamer{
    Id m_id; //номер игрока за столом
    QString m_name; //ник игрока
    int m_penalty; //количество предупреждений и штрафов у игрока
    bool m_vote; // был ли выставлен кто-то на голосование этим игроком
    Id m_vote_id; // номер игрока выставленного на голосование
    bool m_active; // возможность выполнять действия, ставить на голосование
    Role m_role; //роль в игре. 1- мирный, 2 - комиссар, 3 - дон, 4 - мафия.
    Side m_side; // на чьей стороне (для упрощения подсчетов выигрыша проигрыша)

public:
    Gamer(){ //конструктор по-умолчанию
        m_id = Id::ZERO;
        m_name = "";
        m_penalty = 0;
        m_vote = false;
        m_vote_id = Id::ZERO;
        m_active = false;
        m_role = Role::RED;
        m_side = Side::RED;
    }

    Gamer(Id id){ //конструктор с номером игрока
        m_id = id;
        m_name = "";
        m_penalty = 0;
        m_vote = false;
        m_vote_id = Id::ZERO;
        m_active = false;
        m_role = Role::RED;
        m_side = Side::RED;
    }

    Gamer (Id id, Role role, QString name){
        m_id = id;
        m_name = name;
        m_penalty = 0;
        m_vote = false;
        m_vote_id = Id::ZERO;
        m_active = false;
        setRole(role);
    }


    Id getId() { return m_id; }
    void setId(Id id) { m_id = id; }    

    QString getName() { return m_name; }
    void setName(QString name) { m_name = name; }


    int getPenalty() { return m_penalty; }
    void setPenalty(int penalty) { m_penalty = penalty; }
    void penaltyAdd(){m_penalty++;}

    bool getVote() {return m_vote;}
    void setVote(bool vote) { m_vote = vote; }
    void voteReset() { m_vote = false; }

    Id getVoteId() {return m_vote_id;}
    void setVoteId(Id vote_id) { m_vote_id = vote_id; }

    bool getActive() {return m_active;}
    void setActive(bool active)  { m_active = active; }

    Role getRole() {return m_role;}
    void setRole(Role role) {
        m_role = role;
        if (role == Role::MAFIA || role == Role::DON){m_side = Side::MAFIA;}
        if (role == Role::RED || role == Role::POLICMAN){m_side = Side::RED;}
    }

    Side getSide() {return m_side;}   // проверить потом используется ли m_side вообще



    QString printAll(){
        QString print_temp = "";
        print_temp = print_temp + "Id= " + QString::number(m_id) + " Name=" + getName() + " Penalty=" +QString::number(m_penalty);

        if (m_vote){
            print_temp = print_temp + " Vote= true it is:" + QString::number(m_vote_id);
        }
        else{
            print_temp = print_temp + " Vote= false";
        }
        if (m_active){
            print_temp = print_temp + " Active= true";
        }
        else{
            print_temp = print_temp + " Active= false";
        }

        print_temp = print_temp + " Role= " + QString::number(static_cast<int>(m_role)) + " Side= " + QString::number(static_cast<int>(m_side));
        return print_temp;

    }

};


//*************************************//*************************************

class Mafia: public Gamer {
    int m_shooting; //был ли совершен выстрел, при чем только один? Если >1 выстрела , то промах мафии.
    Id m_shooting_id; //в какого игрока совершен выстрел


public:
    Mafia(){
        m_shooting = 0;
        m_shooting_id = Id::ZERO;
        setRole(Role::MAFIA);
    }

    Mafia(Id id) { //конструктор с номером игрока
        setId(id);
        m_shooting = 0;
        m_shooting_id = Id::ZERO;
        setRole(Role::MAFIA);
    }
    Mafia (Id id, Role role, QString name){
        setId(id);
        setName(name);
        m_shooting = 0;
        m_shooting_id = Id::ZERO;
        setRole(role);
    }

    int getShooting() {return m_shooting;}
    void shootingAdd() { m_shooting ++;}
    void shootingReset() {m_shooting = 0;}

    Id getShootingId() {if(m_shooting==1){return m_shooting_id;}else{return Id::ZERO;}}
    void setShootingId(Id shooting_id) {  if (m_shooting == 1){ m_shooting_id = shooting_id;}else{m_shooting_id = Id::ZERO;} }
    void shootingIdReset() {m_shooting_id = Id::ZERO;}
};


//*************************************//*************************************


class Don: public Mafia {
    bool m_check; // Была ли сделана проверка
    Id m_check_id; // В какого игрока сделана проверка

public:
    Don(){
        m_check = false;
        m_check_id = Id::ZERO;
        setRole(Role::DON);
    }
    Don(Id id){ //конструктор с номером игрока
        setId(id);
        m_check = false;
        m_check_id = Id::ZERO;
        setRole(Role::DON);
    }
    Don(Id id, Role role, QString name){
        setId(id);
        setName(name);
        m_check = false;
        m_check_id = Id::ZERO;
        setRole(role);
    }

    bool getCheck() {return m_check;}
    void setCheck(bool check){m_check=check;}
    void checkReset() {m_check = false;}

    Id getCheckId(){if (m_check == true){return m_check_id;}else{return Id::ZERO;}}
    void setCheckId(Id id){if(m_check == true){m_check_id = id;}}
    void checkIdReset() {m_check_id = Id::ZERO;}
};


//*************************************//*************************************


class Policman: public Gamer {
    bool m_check; // Была ли сделана проверка
    Id m_check_id; // В какого игрока сделана проверка

public:
    Policman(){
        m_check = false;
        m_check_id = Id::ZERO;
        setRole(Role::POLICMAN);
    }

    Policman(Id id){ //конструктор с номером игрока
        setId(id);
        m_check = false;
        m_check_id = Id::ZERO;
        setRole(Role::POLICMAN);
    }

    Policman(Id id, Role role, QString name){
        setId(id);
        setName(name);
        m_check = false;
        m_check_id = Id::ZERO;
        setRole(role);
    }

    bool getCheck() {return m_check;}
    void setCheck(bool check){m_check=check;}
    void checkReset() {m_check = false;}

    Id getCheckId(){if (m_check == true){return m_check_id;}else{return Id::ZERO;}}
    void setCheckId(Id id){if(m_check == true){m_check_id = id;}}
    void checkIdReset() {m_check_id = Id::ZERO;}

};




#endif // GAMERS_H
