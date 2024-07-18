#include "game.h"

void Game::clear(){
    userOut.clear();
    userStay.clear();
    vec.clear();
}

int Game::calcul(){ // вовращает число игрков продолжающих играть
    //qDebug() << "summ users :" << vec.size();
    //qDebug() << "CALCUL OPEN";

    if(vec.size() == 1){ // если запустил 1 человек
        socket = vec[vec.size()-1].second;
        return 1;
    }

    int countArr [3]{0,0,0};
    for(int i = 0; i < vec.size(); i++){
        switch (vec[i].first){
        case 0:
            countArr[0]++;
            break;
        case 1:
            countArr[1]++;
            break;
        case 2:
            countArr[2]++;
            break;
        }
    }

    // !!! удаление erase с конца иначе при сдвиге элементов цикл пройдётся не по всем

    if(countArr[0] == 0){ // если остутсвует 0 (камень) то удаляем выбывшего
        if(countArr[1] == 0 || countArr[2] == 0){ // ничья если все нажали одну кнопку
            return 0;
        }
        for(int i = vec.size() - 1; i >= 0; i--){
            if(vec[i].first == 1){
                userOut.push_back(vec[i].second);
                vec.erase(vec.begin()+i);
            }
        }
    }
    else if(countArr[1] == 0){ // если остутсвует 1 (ножницы) то удаляем выбывшего
        if(countArr[0] == 0 || countArr[2] == 0){ // ничья если все нажали одну кнопку
            return 0;
        }
        for(int i = vec.size() - 1; i >= 0; i--){
            if(vec[i].first == 2){
                userOut.push_back(vec[i].second);
                vec.erase(vec.begin()+i);
            }
        }
    }
    else if(countArr[2] == 0){ // если остутсвует 2 (бумага) то удаляем выбывшего
        if(countArr[0] == 0 || countArr[1] == 0){ // ничья если все нажали одну кнопку
            return 0;
        }
        for(int i = vec.size() - 1; i >= 0; i--){
            if(vec[i].first == 0){
                userOut.push_back(vec[i].second);
                vec.erase(vec.begin()+i);
            }
        }
    }
    else{
        return 0; // next round
    }

    if(vec.size() == 1){ // если остался последний игрок то он пойдёт за водой
        socket = vec[vec.size()-1].second;

    }
    else{ // если "победитель" не определился то сохраняем список тех кто остался
        for(int i = 0; i < vec.size(); i++){
            userStay.push_back(vec[i].second);
        }
    }
    return vec.size();
}

void Game::getValGame(int number, QTcpSocket *socket){
    vec.push_back(std::make_pair (number,socket));
}

