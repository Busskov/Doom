#include <model.h>
#include <cmath>

Model::Model() {
    player = Player();
    monsters = Monsters();
    map = Map();
    score = 0;
    gravity = 10;
}

Model::Model
(Player newPlayer, Monsters newMonsters, Map newMap, int newScore, double newGravity) {
    player = newPlayer;
    monsters = newMonsters;
    map = newMap;
    score = newScore;
    gravity = newGravity;
}

Player& Model::getPlayer() {
    return player;
}

Monsters& Model::getMonsters() {
    return monsters;
}

const Map& Model::getMap() const {
    return map;
}

double Model::getGravity() const {
    return gravity;
}

void Model::setGravity(double value) {
    gravity = value;
}

int Model::getScore() const {
    return score;
}

void Model::increaseScore() {
    ++score;
}

void Model::moveMonsters(double interval) {
    for (std::size_t i = 0; i < monsters.getMonsters().size(); ++i) {
        monsters.getMonsters()[i].moveToPlayer(player, interval);
    }
}

void Model::jumpPlayerUpdate(double interval) {
    double newVerticalSpeed = player.getVerticalSpeed() - gravity * interval;
    double jumpHeight =
            player.getJumpHeight() + (newVerticalSpeed + player.getVerticalSpeed()) / 2 * interval;
    if (jumpHeight < 0) {
        jumpHeight = 0;
        newVerticalSpeed = 0;
    }
    player.setVerticalSpeed(newVerticalSpeed);
    player.setJumpHeight(jumpHeight);
}

bool Model::isPlayerDied() {
    std::vector<Monster>& arrayMonsters = monsters.getMonsters();
    const QPointF& point = player.getPosition();
    for (std::size_t i = 0; i < arrayMonsters.size(); ++i) {
        const QPointF& monsterPos = arrayMonsters[i].getPosition();
        double length =
                sqrt((point.x() - monsterPos.x())*(point.x() - monsterPos.x())
                     + (point.y() - monsterPos.y())*(point.y() - monsterPos.y()));
        if (length < player.getHitboxRadius() + arrayMonsters[i].getHitboxRadius()
                && arrayMonsters[i].getHeight() >= player.getJumpHeight()) {
            return 1;
        }
    }
    return 0;
}
