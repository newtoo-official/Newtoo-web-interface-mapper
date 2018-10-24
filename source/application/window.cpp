#include "window.h"
#include "ui_window.h"

namespace NewtooWebInterfaceMapper_application
{
    Window::Window(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::Window),
        mAbout(new About()),
        mFinish(new Finish(this)),
        mOptions(new Options()),
        mHeaderOutput(new Output(headerOutputCaption())),
        mSourceOutput(new Output(sourceOutputCaption()))
    {
        ui->setupUi(this);

        connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));
        connect(ui->actionConvert, SIGNAL(triggered()), this, SLOT(convert()));
        connect(ui->actionHeader_output, SIGNAL(triggered()), this, SLOT(showHeaderOutput()));
        connect(ui->actionSource_code_output, SIGNAL(triggered()), this, SLOT(showSourceOutput()));
        connect(ui->actionConversion_result, SIGNAL(triggered()), this, SLOT(showConversionResult()));
        connect(ui->actionOptions, SIGNAL(triggered()), this, SLOT(showOptions()));
        connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(quit()));
        connect(ui->menuWindow, SIGNAL(aboutToShow()), this, SLOT(updateWindowMenu()));
    }

    About* Window::about() const
    {
        return mAbout;
    }
    Finish* Window::finish() const
    {
        return mFinish;
    }
    Options* Window::options() const
    {
        return mOptions;
    }
    Output* Window::headerOutput() const
    {
        return mHeaderOutput;
    }
    Output* Window::sourceOutput() const
    {
        return mSourceOutput;
    }

    QString Window::headerOutputCaption()
    {
        return QString("C++ header (.h)");
    }
    QString Window::sourceOutputCaption()
    {
        return QString("C++ source code (.cpp)");
    }

    void Window::showAbout()
    {
        about()->show();
    }
    void Window::showOptions()
    {
        options()->loadSettings();
        options()->show();
    }

    void Window::showHeaderOutput()
    {
        headerOutput()->isHidden() ? headerOutput()->show() : headerOutput()->hide();
    }
    void Window::showSourceOutput()
    {
        sourceOutput()->isHidden() ? sourceOutput()->show() : sourceOutput()->hide();
    }
    void Window::showConversionResult()
    {
        finish()->isHidden() ? finish()->show() : finish()->hide();
    }

    void Window::updateWindowMenu()
    {
        headerOutput()->isHidden() ? ui->actionHeader_output->setChecked(false)
                                   : ui->actionHeader_output->setChecked(true);
        sourceOutput()->isHidden() ? ui->actionSource_code_output->setChecked(false)
                                   : ui->actionSource_code_output->setChecked(true);
        finish()->isHidden() ? ui->actionConversion_result->setChecked(false)
                             : ui->actionConversion_result->setChecked(true);
    }

    void Window::convert()
    {
        // convert
        finish()->show();
    }

    void Window::quit()
    {
        close();
    }

    Window::~Window()
    {
        delete ui;

        delete mAbout;
        delete mFinish;
        delete mOptions;
        delete mHeaderOutput;
        delete mSourceOutput;
    }
}
