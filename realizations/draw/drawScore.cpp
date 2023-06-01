#include <classes/view.h>

void View::drawScore(QPainter *painter) {
    Q_UNUSED(painter);
    score->setText(QString::number(model->getScore()));
}
