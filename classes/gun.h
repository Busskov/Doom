#ifndef GUN_H
#define GUN_H

#include <QImage>

class Gun {
public:
    Gun();
    Gun(const Gun& other);
    Gun(QImage, int, int);
    void operator=(const Gun&);

    const QImage& getImage() const;
    int getDamage() const;
    void setFrequency(int);

    bool isReadyToShoot();

private:
    QImage image;
    int damage;
    int frequency;
    int delay;

};

#endif // GUN_H
