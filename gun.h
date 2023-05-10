#ifndef GUN_H
#define GUN_H

#include <QPixmap>

class Gun {
public:
    Gun();
    Gun(QPixmap, int, int);
    void operator=(const Gun&);

    const QPixmap& getImage() const;
    int getDamage() const;
    void setFrequency(int);

    bool isReadyToShoot();

private:
    QPixmap image;
    int damage;
    int frequency;
    int delay;

};

#endif // GUN_H
