#include <controller.h>
#include <QCoreApplication>
#include <cmath>
#include <QDebug>

Controller::Controller(Model *newModel, View *newView, QObject *parent) :
    QObject(parent),
    model(newModel),
    view(newView)
{
    QPoint center = this->view->rect().center();
    QPoint globalCenter = this->view->mapToGlobal(center);
    QCursor::setPos(globalCenter);

    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &Controller::updateView);
    updateTimer->start(1);

    keyA = new QTimer(this);
    keyD = new QTimer(this);
    keyS = new QTimer(this);
    keyW = new QTimer(this);

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
    model->getPlayer().rotate(delta * 1.0 / centerX * M_PI_4);

    QPoint center = this->view->rect().center();
    QPoint globalCenter = this->view->mapToGlobal(center);
    QCursor::setPos(globalCenter);
}

void Controller::leftClicked(QMouseEvent *event) {

}

void Controller::spaceClicked(QKeyEvent *event) {
    if (model->getPlayer().getVerticalSpeed() == 0) {
        model->getPlayer().setVerticalSpeed(10);
    }
}

void Controller::keyAPressed() {
    keyA->start(1);
}

void Controller::keyWPressed() {
    keyW->start(1);
}

void Controller::keyDPressed() {
    keyD->start(1);
}

void Controller::keySPressed() {
    keyS->start(1);
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

void Controller::keyAAction() {
    QPointF position = model->getPlayer().getPosition();
    double angle = model->getPlayer().getAngle();
    angle += M_PI_2;
    double length = model->getPlayer().getSpeed() * (keyA->interval() / 1000.0);
    QPointF resultSpeed(position.x() + length * cos(angle), position.y() - length * sin(angle));
    model->getPlayer().setPosition(resultSpeed);
}

void Controller::keyDAction() {
    QPointF position = model->getPlayer().getPosition();
    double angle = model->getPlayer().getAngle();
    angle -= M_PI_2;
    double length = model->getPlayer().getSpeed() * (keyD->interval() / 1000.0);
    QPointF resultSpeed(position.x() + length * cos(angle), position.y() - length * sin(angle));
    model->getPlayer().setPosition(resultSpeed);
}

void Controller::keyWAction() {
    QPointF position = model->getPlayer().getPosition();
    double angle = model->getPlayer().getAngle();
    double length = model->getPlayer().getSpeed() * (keyW->interval() / 1000.0);
    qDebug() << length;
    QPointF resultSpeed(position.x() + length * cos(angle), position.y() - length * sin(angle));
    model->getPlayer().setPosition(resultSpeed);
}

void Controller::keySAction() {
    QPointF position = model->getPlayer().getPosition();
    double angle = model->getPlayer().getAngle();
    angle += M_PI;
    double length = model->getPlayer().getSpeed() * (keyS->interval() / 1000.0);
    QPointF resultSpeed(position.x() + length * cos(angle), position.y() - length * sin(angle));
    model->getPlayer().setPosition(resultSpeed);
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
