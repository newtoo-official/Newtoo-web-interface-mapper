#pragma once

#include <QPlainTextEdit>
#include <QDialog>
#include "log.h"

namespace Ui
{
    class Finish;
}
namespace webidl2cpp_application
{
    class Window;

    class Finish : public QDialog
    {
        Q_OBJECT

    public:
        explicit Finish(Window* window, QWidget *parent = 0);
        ~Finish();

        Window* window();
        Log& log();

    public slots:

        void showHeader();
        void showSource();

    private:
        Ui::Finish *ui;

        Window* mWindow;
        Log mLog;
    };
}
