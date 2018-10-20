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
    webidl2cpp_application::Finish finish;
    finish.show();
    webidl2cpp_application::About about;
    about.show();
    webidl2cpp_application::Options options;
    options.show();

    return application.exec();
}
