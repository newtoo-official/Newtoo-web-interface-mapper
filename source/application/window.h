#pragma once

#include <QMainWindow>

#include "about.h"
#include "finish.h"
#include "options.h"
#include "output.h"

namespace Ui
{
    class Window;
}
namespace NewtooWebInterfaceMapper_application
{

    class Window : public QMainWindow
    {
        Q_OBJECT

    public:
        explicit Window(QWidget *parent = 0);
        ~Window();

        About* about() const;
        Finish* finish() const;
        Options* options() const;
        Output* headerOutput() const;
        Output* sourceOutput() const;

        static QString headerOutputCaption();
        static QString sourceOutputCaption();

    public slots:

        void showAbout();
        void showOptions();

        void showHeaderOutput();
        void showSourceOutput();
        void showConversionResult();

        void updateWindowMenu();

        void convert();

        void quit();

    private:
        Ui::Window *ui;

        About* mAbout;
        Finish* mFinish;
        Options* mOptions;
        Output* mHeaderOutput;
        Output* mSourceOutput;
    };
}
