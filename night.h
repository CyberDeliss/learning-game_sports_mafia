#ifndef NIGHT_H
#define NIGHT_H

#include <QMainWindow>

namespace Ui {
class Night;
}

class Night : public QMainWindow
{
    Q_OBJECT

public:
    explicit Night(QWidget *parent = nullptr);
    ~Night();

private:
    Ui::Night *ui;
};

#endif // NIGHT_H
