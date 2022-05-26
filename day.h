#ifndef DAY_H
#define DAY_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Day; }
QT_END_NAMESPACE

class Day : public QMainWindow
{
    Q_OBJECT

public:
    Day(QWidget *parent = nullptr);
    ~Day();

private slots:

    void on_buttonVote_clicked();

    void on_buttonCancel_clicked();

private:
    Ui::Day *ui;
};
#endif // DAY_H
