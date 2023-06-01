#include <classes/view.h>
#include <QDebug>
#include <cmath>

void View::drawMonsters(QPainter *painter) {
    std::vector<Monster>& monsters = model->getMonsters().getMonsters();
    const Player& player = model->getPlayer();
    const QPointF& position = player.getPosition();

    // sorting monsters by their length to the player
    std::sort(monsters.begin(), monsters.end(), [player, position](Monster& first, Monster& second) {
        // absolute value
        // use the coordinate transformation formula
        // x' = (x - a1)
        // y' = (y - a2)
        double dxFirst = first.getPosition().x() - position.x();
        double dyFirst = -first.getPosition().y() + position.y();
        double dzFirst = first.getHeight() - player.getHeight() - player.getJumpHeight();

        double lengthFirst = sqrt(dxFirst * dxFirst + dyFirst * dyFirst + dzFirst * dzFirst);

        double dxSecond = second.getPosition().x() - position.x();
        double dySecond = -second.getPosition().y() + position.y();
        double dzSecond = second.getHeight() - player.getHeight() - player.getJumpHeight();

        double lengthSecond =
                sqrt(dxSecond * dxSecond + dySecond * dySecond + dzSecond * dzSecond);

        return lengthFirst > lengthSecond;
    });

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

        // drawing monsters
        QImage image = monsters[i].getImage();
        // half of the width
        int imageWidthHalf = deviation / player.getViewAngle() * (width() / 2.0);
        int imageX = (width() / 2.0) * (1 + angleHorizontal / player.getViewAngle());
        int imageY = height() / 2.0 - width() / 2.0 * angleVertical / player.getViewAngle();
        if (length < 0.0001) {
            continue;
        }

        double radius = monsters[i].getHitboxRadius();
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
