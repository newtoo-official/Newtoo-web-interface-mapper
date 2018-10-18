#pragma once

#include <QMainWindow>

#include "output.h"

namespace Ui
{
    class Window;
}
namespace webidl2cpp_application
{
    class Window : public QMainWindow
    {
        Q_OBJECT

    public:
        explicit Window(QWidget *parent = 0);
        ~Window();

    private:
        Ui::Window *ui;
    };
}
