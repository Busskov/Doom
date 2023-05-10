#include <gun.h>

Gun::Gun() {
    image = QPixmap();
    damage = 1;
    frequency = 0;
    delay = 0;
}

Gun::Gun(QPixmap newImage, int newFrequency, int newDamage) {
    image = newImage;
    frequency = newFrequency;
    damage = newDamage;
    delay = 0;
}

void Gun::operator=(const Gun& other) {
    image = other.image;
    damage = other.damage;
    frequency = other.frequency;
    delay = 0;
}

const QPixmap& Gun::getImage() const {
    return image;
}

int Gun::getDamage() const {
    return damage;
}

void Gun::setFrequency(int value) {
    frequency = value;
}

bool Gun::isReadyToShoot() {
    if (delay == 0) {
        delay = frequency;
        return 1;
    }
    --delay;
    return 0;
}
