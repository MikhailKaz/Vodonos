#ifndef GAME_H
#define GAME_H

#include <QTimer>
#include <QTime>
#include <QDialog>

namespace Ui {
class game;
}

enum RSP { // int
    Rock,
    Scissors,
    Paper
};

class Game : public QDialog
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = 0);
    ~Game();
    void startGame();

private:
    int count;
    int remain = 1;
    Ui::game *ui;
    QTimer *timer;

    void randSelect();

signals:
    void selected(RSP action);

public slots:
    void on_pbRock_clicked();

    void on_pbScissors_clicked();

    void on_pbPaper_clicked();

    void ShowTimer();

};

#endif // GAME_H
