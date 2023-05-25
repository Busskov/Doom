#include <view.h>
#include <QDebug>
#include <cmath>

struct MonsterRelative {
    Monster monster;
    double angleHorizontal;
    double angleVertical;
    double length;
    double deviation;
};

bool comparison(const MonsterRelative& first, const MonsterRelative& second) {
    return first.length > second.length;
}

void View::drawMonsters(QPainter *painter) {
    const std::vector<Monster>& monsters = model->getMonsters().getMonsters();
    const Player& player = model->getPlayer();
    const QPointF& position = player.getPosition();

    std::vector<MonsterRelative> monstersRelative;
    // count monsters' angles relatively to angleLeft
    for (std::size_t i = 0; i < monsters.size(); ++i) {
        // absolute value
        // use the coordinate transformation formula
        // x' = (x - a1)
        // y' = (y - a2)
        double dx = monsters[i].getPosition().x() - position.x();
        double dy = -monsters[i].getPosition().y() + position.y();
        double dz = monsters[i].getHeight() - player.getHeight() - player.getJumpHeight();

        double length = sqrt(dx * dx + dy * dy + dz * dz);

        // deviation of the borders of the monster
        double deviation = asin(monsters[i].getHitboxRadius() / length);

        double angleHorizontal;
        if (dx > -0.000001 && dx < 0.000001) {
            angleHorizontal = (M_PI / 2.0) * ((dy < 0) ? -1 : 1);
        } else {
            angleHorizontal = atan(dy / dx) + ((dx < 0) ? M_PI : 0);
        }
        if (angleHorizontal < 0) {
            angleHorizontal += 2 * M_PI;
        }

        // recount angle relatively to center [-pi, pi]
        angleHorizontal = player.getAngle() - angleHorizontal;
        if (angleHorizontal < -M_PI) {
            angleHorizontal += 2 * M_PI;
        }
        if (angleHorizontal > M_PI) {
            angleHorizontal -= 2 * M_PI;
        }

        double angleVertical;
        angleVertical = asin(dz / length);
        if (angleHorizontal > (M_PI / 2) || angleHorizontal < (-M_PI / 2)) {
            if (angleVertical >= 0) {
                angleVertical = M_PI - angleVertical;
            } else {
                angleVertical = -M_PI - angleVertical;
            }
        }
        // it can't be less than -pi, because viewAngle < pi / 2
        monstersRelative.push_back(MonsterRelative({monsters[i], angleHorizontal, angleVertical, length, deviation}));
    }
    // sorting monsters by their length to the player
    std::sort(monstersRelative.begin(), monstersRelative.end(), comparison);

    // drawing monsters
    for (std::size_t i = 0; i < monstersRelative.size(); ++i) {
        const MonsterRelative& monsterRelative = monstersRelative[i];
        QImage image = monsterRelative.monster.getImage();
        // half of the width
        int imageWidthHalf = monsterRelative.deviation / player.getViewAngle() * (width() / 2.0);
        int imageX = (width() / 2.0) * (1 + monsterRelative.angleHorizontal / player.getViewAngle());
        int imageY = height() / 2.0 - width() / 2.0 * monsterRelative.angleVertical / player.getViewAngle();
        if (monsterRelative.length < 0.0001) {
            continue;
        }

        double length = monsterRelative.length;
        double radius = monsterRelative.monster.getHitboxRadius();
        int newWidth = sqrt(length * length - radius * radius) / length * image.width();
        QImage newImage(image.width(), image.height(), QImage::Format_ARGB32);
        newImage.fill(Qt::transparent);

        QPainter changer(&newImage);
        changer.setRenderHint(QPainter::Antialiasing);
        changer.setBrush(QBrush(image));
        changer.setPen(Qt::NoPen);
        changer.drawEllipse
                ((newImage.width() - newWidth) / 2, (newImage.height() - newWidth) / 2, newWidth, newWidth);

        QImage finalImage = newImage.copy((newImage.width() - newWidth) / 2, (newImage.height() - newWidth) / 2, newWidth, newWidth);

        painter->
                drawImage(imageX - imageWidthHalf, imageY - imageWidthHalf,
                          finalImage.scaled(2 * imageWidthHalf, 2 * imageWidthHalf, Qt::KeepAspectRatio));
    }
}
