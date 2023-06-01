#include <classes/model.h>
#include <cmath>

Model::Model(QObject* parent) : QObject(parent) {
    soundPlayer = new QMediaPlayer(this);
    QMediaPlaylist* playList = new QMediaPlaylist(this);
    playList->addMedia(QUrl("qrc:/sounds/sounds/back.mp3"));
    playList->setPlaybackMode(QMediaPlaylist::Loop);
    soundPlayer->setPlaylist(playList);
    soundPlayer->play();

    player = Player();
    monsters = Monsters();
    map = Map();
    score = 0;
    gravity = 10;

    injured = new QMediaPlayer(this);
    injured->setMedia(QUrl("qrc:/sounds/sounds/injured.mp3"));
    killed = new QMediaPlayer(this);
    killed->setMedia(QUrl("qrc:/sounds/sounds/killed.mp3"));
}

Model::Model
(Player newPlayer, Monsters newMonsters, Map newMap, int newScore, double newGravity, QObject* parent) :
    QObject(parent)
{
    soundPlayer = new QMediaPlayer(this);
    QMediaPlaylist* playList = new QMediaPlaylist(this);
    playList->addMedia(QUrl("qrc:/sounds/sounds/back.mp3"));
    playList->setPlaybackMode(QMediaPlaylist::Loop);
    soundPlayer->setPlaylist(playList);
    soundPlayer->play();

    player = newPlayer;
    monsters = newMonsters;
    map = newMap;
    score = newScore;
    gravity = newGravity;

    injured = new QMediaPlayer(this);
    injured->setMedia(QUrl("qrc:/sounds/sounds/injured.mp3"));
    killed = new QMediaPlayer(this);
    killed->setMedia(QUrl("qrc:/sounds/sounds/killed.mp3"));
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
        double dx = monsterPos.x() - point.x();
        double dy = monsterPos.y() - point.y();
        double dz = arrayMonsters[i].getHeight() - player.getHeight() - player.getJumpHeight();
        double length = sqrt(dx * dx + dy * dy + dz * dz);
        if (length < player.getHitboxRadius() + arrayMonsters[i].getHitboxRadius()) {
            return 1;
        }
    }
    return 0;
}

void Model::killMonster() {
    killed->play();
}

void Model::injureMonster() {
    injured->play();
}
