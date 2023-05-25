#include <classes/monster.h>
#include <QPainter>
#include <cmath>

Monster::Monster() {
    image = QImage();
    height = 2;
    position = QPointF(0, 0);
    health = 1;
    hitboxRadius = 0.5;
    speed = 1;
}

Monster::Monster
(QImage newImage, double newHeight, QPointF newPosition,
int newHealth, double newHitboxRadius, double newSpeed) {
    image = newImage;
    height = newHeight;
    position = newPosition;
    health = newHealth;
    hitboxRadius = newHitboxRadius;
    speed = newSpeed;
}

double Monster::getSpeed() const {
    return speed;
}

void Monster::setSpeed(double value) {
    speed = value;
}

const QImage& Monster::getImage() const {
    return image;
}

double Monster::getHeight() const {
    return height;
}

const QPointF& Monster::getPosition() const {
    return position;
}

void Monster::setPosition(const QPointF& value) {
    position = value;
}

double Monster::getHitboxRadius() const {
    return hitboxRadius;
}

void Monster::moveToPlayer(const Player& player, double interval) {
    const QPointF& point = player.getPosition();
    double length = sqrt((point.x() - position.x())*(point.x() - position.x())
                         + (point.y() - position.y())*(point.y() - position.y()));
    double moveLength = speed * interval;
    double newX = position.x() + (moveLength / length) * (point.x() - position.x());
    double newY = position.y() + (moveLength / length) * (point.y() - position.y());
    position = QPointF(newX, newY);
}

bool Monster::isDead() const {
    if (health == 0) {
        return 1;
    }
    return 0;
}

void Monster::hit(int damage) {
    health -= damage;
    if (health < 0) {
        health = 0;
    }
    QImage newImage = image;
    QPainter painter(&newImage);
    painter.fillRect(newImage.rect(), QColor(255, 0, 0, 35));
    image = newImage;
}
