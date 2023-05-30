#include <classes/gun.h>
#include <QFileInfo>
#include <QDebug>

Gun::Gun(QObject* parent) : QObject(parent) {
    player = new QMediaPlayer(this);
    player->setMedia(QUrl("qrc:/sounds/sounds/simpleGun.mp3"));

    image = QImage();
    damage = 1;
    frequency = 0;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Gun::stopDelay);
}

Gun::Gun(const Gun& other) : QObject(other.parent()){
    player = other.player;

    image = other.image;
    frequency = other.frequency;
    damage = other.damage;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Gun::stopDelay);
}

Gun::Gun(QImage newImage, int newFrequency, int newDamage, QObject* parent) :
    QObject(parent)
{
    player = new QMediaPlayer(this);
    player->setMedia(QUrl("qrc:/sounds/sounds/simpleGun.mp3"));

    image = newImage;
    frequency = newFrequency;
    damage = newDamage;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Gun::stopDelay);
}

void Gun::operator=(const Gun& other) {
    image = other.image;
    damage = other.damage;
    frequency = other.frequency;
}

const QImage& Gun::getImage() const {
    return image;
}

int Gun::getDamage() const {
    return damage;
}

void Gun::setFrequency(int value) {
    frequency = value;
}

bool Gun::isReadyToShoot() {
    if (timer->isActive()) {
        return 0;
    }
    player->play();
    timer->start(frequency);
    return 1;
}

void Gun::stopDelay() {
    timer->stop();
}
