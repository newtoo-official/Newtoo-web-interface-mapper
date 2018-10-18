#include "window.h"
#include "ui_window.h"

namespace webidl2cpp_application
{
    Window::Window(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::Window)
    {
        ui->setupUi(this);
    }

    Window::~Window()
    {
        delete ui;
    }
}
