#include <classes/view.h>

#include <QApplication>
#include <QColor>
#include <cmath>
#include <QDebug>
#include <classes/controller.h>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    std::vector<QPointF> vertices =
    {QPointF(-60, -60), QPointF(-60, 60), QPointF(60, 60), QPointF(60, -60)};
    Map map(vertices, 3);

    Gun gun(QImage(":/images/images/gun.png"), 1000, 10);
    Player player(QPointF(0, 0), 0, M_PI_4, 2, 0.5, 10, 0, gun);
    Model model(player, Monsters(), map, 0, 10);
    View view(&model);
    Controller controller(&model, &view);
    view.show();
    return application.exec();
}
