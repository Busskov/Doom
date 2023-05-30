#ifndef GUN_H
#define GUN_H

#include <QImage>
#include <QObject>
#include <QTimer>
#include <QMediaPlayer>

class Gun : public QObject {
    Q_OBJECT
public:
    Gun(QObject* parent = nullptr);
    Gun(const Gun& other);
    Gun(QImage, int, int, QObject* parent = nullptr);
    void operator=(const Gun&);

    const QImage& getImage() const;
    int getDamage() const;
    void setFrequency(int);

    bool isReadyToShoot();

private slots:
    void stopDelay();

private:
    QImage image;
    int damage;
    int frequency;
    QTimer *timer;
    QMediaPlayer* player;
};

#endif // GUN_H
