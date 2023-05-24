#include <controller.h>
#include <QCoreApplication>
#include <cmath>
#include <QDebug>
#include <QTime>

Controller::Controller(Model *newModel, View *newView, QObject *parent) :
    QObject(parent),
    model(newModel),
    view(newView)
{
    updateTimer = new QTimer(this);
    updateTimer->setTimerType(Qt::PreciseTimer);
    connect(updateTimer, &QTimer::timeout, this, &Controller::updateView);
    updateTimer->start(15);

    generateMonsterTimer = new QTimer(this);
    connect(generateMonsterTimer, &QTimer::timeout, this, &Controller::generateMonster);
    generateMonsterTimer->start(10'000);

    keyA = new QTimer(this);
    keyD = new QTimer(this);
    keyS = new QTimer(this);
    keyW = new QTimer(this);
    keyA->setTimerType(Qt::PreciseTimer);
    keyD->setTimerType(Qt::PreciseTimer);
    keyS->setTimerType(Qt::PreciseTimer);
    keyW->setTimerType(Qt::PreciseTimer);

    connect(keyA, &QTimer::timeout, this, &Controller::keyAAction);
    connect(keyW, &QTimer::timeout, this, &Controller::keyWAction);
    connect(keyD, &QTimer::timeout, this, &Controller::keyDAction);
    connect(keyS, &QTimer::timeout, this, &Controller::keySAction);

    connect(view, &View::mouseMove, this, &Controller::mouseMove);
    connect(view, &View::leftClick, this, &Controller::leftClicked);
    connect(view, &View::spaceClicked, this, &Controller::spaceClicked);

    connect(view, &View::keyAPressed, this, &Controller::keyAPressed);
    connect(view, &View::keyWPressed, this, &Controller::keyWPressed);
    connect(view, &View::keySPressed, this, &Controller::keySPressed);
    connect(view, &View::keyDPressed, this, &Controller::keyDPressed);

    connect(view, &View::keyAReleased, this, &Controller::keyAReleased);
    connect(view, &View::keyDReleased, this, &Controller::keyDReleased);
    connect(view, &View::keySReleased, this, &Controller::keySReleased);
    connect(view, &View::keyWReleased, this, &Controller::keyWReleased);
}

void Controller::mouseMove(QMouseEvent *event) {
    int centerX = view->width() / 2;
    int delta = centerX - event->x();
    model->getPlayer().rotate(delta * 1.0 / centerX * model->getPlayer().getViewAngle());

    QPoint center = this->view->rect().center();
    QPoint globalCenter = this->view->mapToGlobal(center);
    QCursor::setPos(globalCenter);
}

void Controller::spaceClicked(QKeyEvent *event) {
    Q_UNUSED(event);
    if (model->getPlayer().getVerticalSpeed() == 0) {
        model->getPlayer().setVerticalSpeed(10);
    }
}

void Controller::keyAPressed() {
    keyA->start(15);
}

void Controller::keyWPressed() {
    keyW->start(15);
}

void Controller::keyDPressed() {
    keyD->start(15);
}

void Controller::keySPressed() {
    keyS->start(15);
}

void Controller::keyAReleased() {
    keyA->stop();
}

void Controller::keyWReleased() {
    keyW->stop();
}

void Controller::keyDReleased() {
    keyD->stop();
}

void Controller::keySReleased() {
    keyS->stop();
}

void inMap(const std::vector<QPointF>& vertices, double hitbox, QPointF& point) {
    if (point.x() < vertices[0].x() + hitbox) {
        point.setX(vertices[0].x() + hitbox);
    }
    if (point.x() > vertices[2].x() - hitbox) {
        point.setX(vertices[2].x() - hitbox);
    }
    if (point.y() < vertices[0].y() + hitbox) {
        point.setY(vertices[0].y() + hitbox);
    }
    if (point.y() > vertices[2].y() - hitbox) {
        point.setY(vertices[2].y() - hitbox);
    }
}

void Controller::keyAAction() {
    QPointF position = model->getPlayer().getPosition();
    double angle = model->getPlayer().getAngle();
    angle += M_PI_2;
    double length = model->getPlayer().getSpeed() * (keyA->interval() / 1000.0);
    QPointF result(position.x() + length * cos(angle), position.y() - length * sin(angle));

    inMap(model->getMap().getVertices(), model->getPlayer().getHitboxRadius(), result);
    model->getPlayer().setPosition(result);
}

void Controller::keyDAction() {
    QPointF position = model->getPlayer().getPosition();
    double angle = model->getPlayer().getAngle();
    angle -= M_PI_2;
    double length = model->getPlayer().getSpeed() * (keyD->interval() / 1000.0);
    QPointF result(position.x() + length * cos(angle), position.y() - length * sin(angle));

    inMap(model->getMap().getVertices(), model->getPlayer().getHitboxRadius(), result);
    model->getPlayer().setPosition(result);
}

void Controller::keyWAction() {
    QPointF position = model->getPlayer().getPosition();
    double angle = model->getPlayer().getAngle();
    double length = model->getPlayer().getSpeed() * (keyW->interval() / 1000.0);
    QPointF result(position.x() + length * cos(angle), position.y() - length * sin(angle));

    inMap(model->getMap().getVertices(), model->getPlayer().getHitboxRadius(), result);
    model->getPlayer().setPosition(result);
}

void Controller::keySAction() {
    QPointF position = model->getPlayer().getPosition();
    double angle = model->getPlayer().getAngle();
    angle += M_PI;
    double length = model->getPlayer().getSpeed() * (keyS->interval() / 1000.0);
    QPointF result(position.x() + length * cos(angle), position.y() - length * sin(angle));

    inMap(model->getMap().getVertices(), model->getPlayer().getHitboxRadius(), result);
    model->getPlayer().setPosition(result);
}

void Controller::updateView() {
    double interval = updateTimer->interval() * 1.0 / 1000;
    model->jumpPlayerUpdate(interval);
    model->moveMonsters(interval);
    if (model->isPlayerDied()) {
        QCoreApplication::quit();
    }
    view->repaint();
}

void Controller::generateMonster() {
    QImage imageMonster = QImage(100, 100, QImage::Format_RGB32);
    imageMonster.fill(QColor("red"));
    Monster monster(imageMonster, 2.5, QPointF(20, 0), 10, 2, 2);
    model->getMonsters().addMonster(monster);
}
