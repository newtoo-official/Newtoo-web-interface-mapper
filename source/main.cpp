#include <QApplication>

#include "application/window.h"
#include "application/output.h"
#include "application/options.h"
#include "application/finish.h"
#include "application/about.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    webidl2cpp_application::Window appw;
    appw.show();

    return application.exec();
}
