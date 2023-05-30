#include <classes/player.h>
#include <cmath>

Player::Player() {
    position = QPointF(0, 0);
    angle = 0;
    viewAngle = M_PI_4;
    height = 2;
    hitboxRadius = 0.5;
    speed = 10;
    verticalSpeed = 0;
    jumpHeight = 0;
    gun = Gun();
}

Player::Player
(const QPointF& newPosition, double newAngle, double newViewAngle, double newHeight,
 double newHitboxRadius, double newSpeed, double newVerticalSpeed, Gun newGun) {
    position = newPosition;
    angle = newAngle;
    viewAngle = newViewAngle;
    height = newHeight;
    hitboxRadius = newHitboxRadius;
    speed = newSpeed;
    verticalSpeed = newVerticalSpeed;
    gun = newGun;
}

const QPointF& Player::getPosition() const {
    return position;
}

void Player::setPosition(const QPointF& value) {
    position = value;
}

double Player::getAngle() const {
    return angle;
}

void Player::setAngle(double value) {
    angle = value;
}

double Player::getViewAngle() const {
    return viewAngle;
}

void Player::setViewAngle(double value) {
    viewAngle = value;
}

double Player::getHeight() const {
    return height;
}

void Player::setHeight(double value) {
    height = value;
}

double Player::getHitboxRadius() const {
    return hitboxRadius;
}

void Player::setHitboxRadius(double value) {
    hitboxRadius = value;
}

double Player::getSpeed() const {
    return speed;
}

void Player::setSpeed(double value) {
    speed = value;
}

double Player::getVerticalSpeed() const {
    return verticalSpeed;
}

void Player::setVerticalSpeed(double value) {
    verticalSpeed = value;
}

double Player::getJumpHeight() const {
    return jumpHeight;
}

void Player::setJumpHeight(double value) {
    jumpHeight = value;
}

Gun& Player::getGun() {
    return gun;
}

void Player::setGun(const Gun& value) {
    gun = value;
}


void Player::rotate(double addAngle) {
    angle += addAngle;
    if (angle >= 2 * M_PI) {
        angle -= 2 * M_PI;
    }
    if (angle < 0) {
        angle += 2 * M_PI;
    }
}
