#include <controller.h>
#include <cmath>
#include <algorithm>
#include <QDebug>

struct MonsterRelative {
    Monster monster;
    double angle;
    double length;
    double deviation;
};

bool comparisonLength(const MonsterRelative& first, const MonsterRelative& second) {
    return first.length < second.length;
}

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

        double length = sqrt(dx * dx + dy * dy);
        // deviation of the borders of the monster
        double deviation = asin(monsters[i].getHitboxRadius() / length);

        double angle;
        if (dx > -0.000001 && dx < 0.000001) {
            angle = (M_PI / 2.0) * ((dy < 0) ? -1 : 1);
        } else {
            angle = atan(dy / dx) + ((dx < 0) ? M_PI : 0);
        }
        if (angle < 0) {
            angle += 2 * M_PI;
        }

        // recount angle relatively to center [-pi, pi]
        angle = player.getAngle() - angle;
        if (angle < -M_PI) {
            angle += 2 * M_PI;
        }
        if (angle > M_PI) {
            angle -= 2 * M_PI;
        }

        double rightAngle = angle + deviation;
        double leftAngle = angle - deviation;
        if (rightAngle >= 0 && leftAngle <= 0) {
            monsters[i].hit(player.getGun().getDamage());
            if (monsters[i].isDead()) {
                model->getMonsters().removeMonster(i);
            }
            return;
        }
    }
}
