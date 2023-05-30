#ifndef MODEL_H
#define MODEL_H

#include <classes/monsters.h>
#include <classes/map.h>
#include <classes/player.h>
#include <QMediaPlayer>
#include <QMediaPlayList>
#include <QObject>

class Model : public QObject {
    Q_OBJECT
public:
    Model(QObject* parent = nullptr);
    Model(Player, Monsters, Map, int, double, QObject* parent = nullptr);

    Player& getPlayer();
    Monsters& getMonsters();
    const Map& getMap() const;

    int getScore() const;
    void increaseScore();

    double getGravity() const;
    void setGravity(double);

    void moveMonsters(double interval);
    void jumpPlayerUpdate(double interval);
    bool isPlayerDied();

private:
    Player player;
    Monsters monsters;
    Map map;
    int score;
    double gravity;
    QMediaPlayer* soundPlayer;
};

#endif // MODEL_H
