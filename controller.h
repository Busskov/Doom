#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <model.h>
#include <view.h>
#include <QObject>
#include <QTimer>
#include <QPoint>

class Controller : public QObject {
    Q_OBJECT

public:
    Controller(Model *newModel, View *newView, QObject *parent = nullptr);

public slots:
    void updateView();

    void generateMonster();

    void mouseMove(QMouseEvent *event);
    void leftClicked(QMouseEvent *event);
    void spaceClicked(QKeyEvent *event);

    void keyAPressed();
    void keyWPressed();
    void keyDPressed();
    void keySPressed();

    void keyAReleased();
    void keyWReleased();
    void keyDReleased();
    void keySReleased();

    void keyAAction();
    void keyWAction();
    void keyDAction();
    void keySAction();

private:
    Model* model;
    View* view;

    QTimer* updateTimer;
    QTimer* generateMonsterTimer;
    QTimer* keyA;
    QTimer* keyW;
    QTimer* keyD;
    QTimer* keyS;
};

#endif // CONTROLLER_H
