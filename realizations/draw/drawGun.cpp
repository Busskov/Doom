#include <classes/view.h>
#include <QDebug>

void View::drawGun(QPainter *painter) {
    QPen pen(QColor(0, 0, 0), 3);
    painter->setPen(pen);
    int width = this->width() / 2;
    int height = this->height() / 2;
    QPoint start(width, height - 4);
    QPoint end(width, height + 4);
    painter->drawLine(start, end);
    start = QPoint(width - 4, height);
    end = QPoint(width + 4, height);
    painter->drawLine(start, end);

    QImage image = model->getPlayer().getGun().getImage().scaled(0.350 * this->width(), 0.350 * this->height());
    painter->drawImage(this->width() - image.width(), this->height() - image.height(), image);
}
