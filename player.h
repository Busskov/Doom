#ifndef PLAYER_H
#define PLAYER_H

#include <QPointF>
#include <gun.h>

class Player {
public:
    Player();
    Player(const QPointF&, double, double, double, double, double, double, Gun);

    const QPointF& getPosition() const;
    void setPosition(const QPointF&);
    double getAngle() const;
    void setAngle(double);
    double getViewAngle() const;
    void setViewAngle(double);
    double getHeight() const;
    void setHeight(double);
    double getHitboxRadius() const;
    void setHitboxRadius(double);
    double getSpeed() const;
    void setSpeed(double);
    double getVerticalSpeed() const;
    void setVerticalSpeed(double);
    double getJumpHeight() const;
    void setJumpHeight(double);

    const Gun& getGun() const;
    void setGun(const Gun&);


    void rotate(double);

private:
    QPointF position;
    double angle;
    double viewAngle;
    double height;
    double hitboxRadius;

    double speed;
    double verticalSpeed;

    double jumpHeight;

    Gun gun;
};

#endif // PLAYER_H
