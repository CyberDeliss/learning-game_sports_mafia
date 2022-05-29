#include "day.h"
#include "ui_day.h"
#include "gamers.h"


Day::Day(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Day)
{
    ui->setupUi(this);
}


Day::~Day()
{
    delete ui;
}

void Day::on_buttonVote_clicked()
{


    ui->gamer_1->setFrameShape(QFrame::Panel);
    ui->gamer_2->setFrameShape(QFrame::Panel);
    ui->gamer_3->setFrameShape(QFrame::Panel);
    ui->gamer_4->setFrameShape(QFrame::Panel);
    ui->gamer_5->setFrameShape(QFrame::Panel);
    ui->gamer_6->setFrameShape(QFrame::Panel);
    ui->gamer_7->setFrameShape(QFrame::Panel);
    ui->gamer_8->setFrameShape(QFrame::Panel);
    ui->gamer_9->setFrameShape(QFrame::Panel);
    ui->gamer_10->setFrameShape(QFrame::Panel);

    ui->gamer_1->setFrameShadow(QFrame::Raised);
    ui->gamer_2->setFrameShadow(QFrame::Raised);
    ui->gamer_3->setFrameShadow(QFrame::Raised);
    ui->gamer_4->setFrameShadow(QFrame::Raised);
    ui->gamer_5->setFrameShadow(QFrame::Raised);
    ui->gamer_6->setFrameShadow(QFrame::Raised);
    ui->gamer_7->setFrameShadow(QFrame::Raised);
    ui->gamer_8->setFrameShadow(QFrame::Raised);
    ui->gamer_9->setFrameShadow(QFrame::Raised);
    ui->gamer_10->setFrameShadow(QFrame::Raised);



}


void Day::on_buttonCancel_clicked()
{
    ui->gamer_1->setFrameShape(QFrame::NoFrame);
    ui->gamer_2->setFrameShape(QFrame::NoFrame);
    ui->gamer_3->setFrameShape(QFrame::NoFrame);
    ui->gamer_4->setFrameShape(QFrame::NoFrame);
    ui->gamer_5->setFrameShape(QFrame::NoFrame);
    ui->gamer_6->setFrameShape(QFrame::NoFrame);
    ui->gamer_7->setFrameShape(QFrame::NoFrame);
    ui->gamer_8->setFrameShape(QFrame::NoFrame);
    ui->gamer_9->setFrameShape(QFrame::NoFrame);
    ui->gamer_10->setFrameShape(QFrame::NoFrame);

}

