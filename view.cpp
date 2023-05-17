#include "view.h"
#include <cmath>
#include <algorithm>
#include <QDebug>
#include <QCoreApplication>

View::View(Model *newModel, QWidget *parent)
    : QMainWindow(parent),
    model(newModel)
{
//    QPoint center = this->rect().center();
//    QPoint globalCenter = this->mapToGlobal(center);
//    QCursor::setPos(globalCenter);

    this->resize(1200, 800);
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
