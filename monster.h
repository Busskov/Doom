#ifndef MONSTER_H
#define MONSTER_H

#include <player.h>
#include <QImage>
#include <QPointF>

class Monster {
public:
    Monster();
    Monster(QImage, double, QPointF, int, double, double);

    double getSpeed() const;
    void setSpeed(double);
    const QImage& getImage() const;
    double getHeight() const;
    const QPointF& getPosition() const;
    void setPosition(const QPointF&);
    double getHitboxRadius() const;

    void moveToPlayer(const Player&, double interval);
    bool isDead() const;
    void hit(int damage);

private:
    QImage image;
    double height;
    QPointF position;
    int health;
    double hitboxRadius;
    double speed;

};

#endif // MONSTER_H
