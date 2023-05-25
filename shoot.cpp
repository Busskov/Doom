#include <controller.h>
#include <cmath>
#include <algorithm>
#include <QDebug>

void Controller::leftClicked(QMouseEvent *event) {
    Q_UNUSED(event);
    std::vector<Monster>& monsters = model->getMonsters().getMonsters();

    const Player& player = model->getPlayer();
    const QPointF& position = player.getPosition();

    std::sort(monsters.begin(), monsters.end(), [position](const Monster& first, const Monster& second) {
        // absolute value
        // use the coordinate transformation formula
        // x' = (x - a1)
        // y' = (y - a2)
        double dxFirst = first.getPosition().x() - position.x();
        double dyFirst = -first.getPosition().y() + position.y();

        double dxSecond = second.getPosition().x() - position.x();
        double dySecond = -second.getPosition().y() + position.y();

        double lengthFirst = sqrt(dxFirst * dxFirst + dyFirst * dyFirst);
        double lengthSecond = sqrt(dxSecond * dxSecond + dySecond * dySecond);
        return lengthFirst < lengthSecond;
    });

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

        double angle;
        // cos(angle) = a*b/(|a|*|b|)
        // a = (cos, -sin, 0)
        double gameAngle = player.getAngle();
        angle = acos((dx * cos(gameAngle) - dy * sin(gameAngle)) / length);

        if (angle <= deviation) {
            monsters[i].hit(player.getGun().getDamage());
            if (monsters[i].isDead()) {
                model->getMonsters().removeMonster(i);
            }
            return;
        }
    }
}
