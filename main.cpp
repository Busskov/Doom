#include "view.h"

#include <QApplication>
#include <controller.h>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    Model model;
    View view(&model);
    Controller controller(&model, &view);
    view.showFullScreen();
    return application.exec();
}
