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

void Monster::setHeight(double newHeight) {
    height = newHeight;
}

double Monster::getHitboxRadius() const {
    return hitboxRadius;
}

void Monster::moveToPlayer(const Player& player, double interval) {
    const QPointF& point = player.getPosition();
    double dx = position.x() - point.x();
    double dy = position.y() - point.y();
    double dz = this->height - player.getHeight() - player.getJumpHeight();
    double length = sqrt(dx * dx + dy * dy + dz * dz);

    double moveLength = speed * interval;
    double newX = position.x() - (moveLength / length) * dx;
    double newY = position.y() - (moveLength / length) * dy;
    double newZ = this->height - (moveLength / length) * dz;
    position = QPointF(newX, newY);
    this->height = newZ;
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
    double intensity = damage * 1.0 / health / 0.1;
    painter.fillRect(newImage.rect(), QColor(255, 0, 0, 20 * intensity));
    image = newImage;
}
