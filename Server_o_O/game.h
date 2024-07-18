#ifndef GAME_H
#define GAME_H

#endif // GAME_H

#include <QTcpSocket>
#include <map>

class Game{

public:

    void clear(); // clear что тут ещё объяснять???
    int calcul(); // возвращает число игроков продолжающих играть
    void getValGame(int number, QTcpSocket *socket); // записываем полученные значение (камень/ножницы/бумага)

    QTcpSocket* socket;
    QVector <QTcpSocket*> userStay; // проигравшие
    QVector <QTcpSocket*> userOut; // выбывшие
    QVector <std::pair <int, QTcpSocket*>> vec; // хранение параметра каждом пользователе и сам сокет
};
