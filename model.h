#ifndef MODEL_H
#define MODEL_H

#include <monsters.h>
#include <map.h>
#include <player.h>

class Model {
public:
    Model();
    Model(Player, Monsters, Map, int, double);

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

};

#endif // MODEL_H
