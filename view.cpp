#include "view.h"
#include <cmath>
#include <algorithm>
#include <QDebug>
#include <QCoreApplication>

View::View(Model *newModel, QWidget *parent)
    : QMainWindow(parent),
    model(newModel)
{
    this->resize(900, 600);
    setMouseTracking(true);
    this->setCursor(Qt::BlankCursor);
}

View::~View() {
    delete model;
}

void View::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    drawWalls(&painter);
    drawMonsters(&painter);
    drawGun(&painter);
    drawScore(&painter);
}

struct Ray {
    QPointF point;
    double angle;
};

bool comparison(const Ray& first, const Ray& second) {
    return first.angle < second.angle;
}

void View::drawWalls(QPainter *painter) {
    // get vertices' angles [0, 2PI]
    const std::vector<QPointF> &vertices = model->getMap().getVertices();
    const Player& player = model->getPlayer();
    const QPointF& position = player.getPosition();
    double angleLeft = player.getAngle() + player.getViewAngle();
    double angleRight = player.getAngle() - player.getViewAngle();
    if (angleLeft >= 2 * M_PI) {
        angleLeft -= 2 * M_PI;
    }
    if (angleRight < 0) {
        angleRight += 2 * M_PI;
    }
    std::vector<Ray> rays;
    // recount angleRight relatively to angleLeft
    double angleRightRelative = angleLeft - angleRight;
    if (angleRightRelative < 0) {
        angleRightRelative += 2 * M_PI;
    }
    // count points angles relatively to angleLeft
    for (std::size_t i = 0; i < vertices.size(); ++i) {
        // absolute value
        // use the coordinate transformation formula
        // x' = (x - a1)cosf + (y - a2)sinf
        // y' = -(x - a1)sinf + (y - a2)cosf
        double dx = vertices[i].x() - position.x();
        double dy = -vertices[i].y() + position.y();
        double angle;
        if (dx > -0.000001 && dx < 0.000001) {
            angle = M_PI * ((dy < 0) ? -1 : 1) / 2;
        } else {
            angle = atan(dy / dx) + ((dx < 0) ? M_PI : 0);
        }
        if (angle < 0) {
            angle += 2 * M_PI;
        }

        // relative value
        angle = angleLeft - angle;
        if (angle < 0) {
            angle += 2 * M_PI;
        }
        if (angle <= angleRightRelative) {
            rays.push_back(Ray({vertices[i], angle}));
        }
    }
    std::sort(rays.begin(), rays.end(), comparison);
    // find intersection between angleLeft and angleRight with map
    QPointF intersectionLeft;
    QPointF intersectionRight;

    double infinity = this->width() + this->height();
    QPointF endViewPointLeft
            (position.x() + infinity * cos(angleLeft), position.y() - infinity * sin(angleLeft));
    QPointF endViewPointRight
            (position.x() + infinity * cos(angleRight), position.y() - infinity * sin(angleRight));
    QLineF viewLineLeft(position, endViewPointLeft);
    QLineF viewLineRight(position, endViewPointRight);

    for (std::size_t i = 0; i < vertices.size(); ++i) {
        QLineF wall(vertices[i], vertices[(i + 1) % vertices.size()]);
        if (wall.intersects(viewLineLeft, &intersectionLeft) == QLineF::BoundedIntersection) {
            break;
        }
    }
    for (std::size_t i = 0; i < vertices.size(); ++i) {
        QLineF wall(vertices[i], vertices[(i + 1) % vertices.size()]);
        if (wall.intersects(viewLineRight, &intersectionRight) == QLineF::BoundedIntersection) {
            break;
        }
    }
    // add angleLeft and angleRight intersection points
    rays.insert(rays.begin(), Ray({intersectionLeft, 0}));
    rays.push_back(Ray({intersectionRight, angleRightRelative}));
    // draw horizontal lines
    QPen pen(QColor(0, 0, 255), 4, Qt::SolidLine, Qt::RoundCap);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(pen);

    std::vector<QPointF> bottomPoints(rays.size());
    std::vector<QPointF> topPoints(rays.size());

    double verticalViewAngle = this->height() * 1.0 / this->width() * model->getPlayer().getViewAngle();
    for (std::size_t i = 0; i < rays.size(); ++i) {
        double length = sqrt((rays[i].point.x() - player.getPosition().x())
                             *(rays[i].point.x() - player.getPosition().x())
                             + (rays[i].point.y() - player.getPosition().y())
                             * (rays[i].point.y() - player.getPosition().y()));
        double verticalAngle = 0;
        // bottom point
        if (length < 0.000001 && length > -0.000001) {
            verticalAngle = M_PI_2;
        } else {
            verticalAngle = atan((player.getJumpHeight() + player.getHeight()) / length);
        }
        bottomPoints[i] = QPointF(rays[i].angle / (2 * player.getViewAngle()) * this->width(),
                                  this->height() / 2.0 * (1 + verticalAngle / verticalViewAngle));
        // top point
        if (length < 0.000001 && length > -0.000001) {
            verticalAngle = M_PI_2;
        } else {
            verticalAngle = atan((player.getJumpHeight() + player.getHeight() - model->getMap().getWallHeight()) / length);
        }
        topPoints[i] = QPointF(rays[i].angle / (2 * player.getViewAngle()) * this->width(),
                               this->height() / 2.0 * (1 + verticalAngle / verticalViewAngle));
    }
    for (std::size_t i = 0; i < rays.size(); ++i) {
        painter->drawLine(bottomPoints[i], topPoints[i]);
    }
    for (std::size_t i = 1; i < rays.size(); ++i) {
        painter->drawLine(bottomPoints[i - 1], bottomPoints[i]);
        painter->drawLine(topPoints[i - 1], topPoints[i]);
    }
}

void View::drawMonsters(QPainter *painter) {

}

void View::drawGun(QPainter *painter) {

}

void View::drawScore(QPainter *painter) {

}

void View::mouseMoveEvent(QMouseEvent *event) {
    emit mouseMove(event);
}

void View::mousePressEvent(QMouseEvent *event) {
    emit leftClick(event);
}

void View::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_A) {
        emit keyAReleased();
    }
    if (event->key() == Qt::Key_W) {
        emit keyWReleased();
    }
    if (event->key() == Qt::Key_S) {
        emit keySReleased();
    }
    if (event->key() == Qt::Key_D) {
        emit keyDReleased();
    }
}

void View::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Space) {
        emit spaceClicked(event);
    }
    if (event->key() == Qt::Key_A) {
        emit keyAPressed();
    }
    if (event->key() == Qt::Key_W) {
        emit keyWPressed();
    }
    if (event->key() == Qt::Key_S) {
        emit keySPressed();
    }
    if (event->key() == Qt::Key_D) {
        emit keyDPressed();
    }
    if (event->key() == Qt::Key_Escape) {
        QCoreApplication::quit();
    }
}
