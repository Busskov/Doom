#include "view.h"

#include <QApplication>
#include <QColor>
#include <controller.h>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    std::vector<QPointF> vertices =
    {QPointF(-40, -40), QPointF(-40, 40), QPointF(80, 40), QPointF(80, -40)};
    Map map(vertices, 3);

    Model model(Player(), Monsters(), map, 0, 10);
    View view(&model);
    Controller controller(&model, &view);
    view.show();
    return application.exec();
}
