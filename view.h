#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <model.h>

class View : public QMainWindow
{
    Q_OBJECT
public:
    View(Model *value, QWidget *parent = nullptr);
    ~View();

signals:
    void mouseMove(QMouseEvent *event);
    void leftClick(QMouseEvent *event);
    void spaceClicked(QKeyEvent *event);
    void keyAPressed();
    void keyWPressed();
    void keyDPressed();
    void keySPressed();

    void keyAReleased();
    void keyWReleased();
    void keyDReleased();
    void keySReleased();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private:
    Model* model;

    void drawWalls(QPainter *);
    void drawMonsters(QPainter *);
    void drawGun(QPainter *);
    void drawScore(QPainter *);

};
#endif // VIEW_H
