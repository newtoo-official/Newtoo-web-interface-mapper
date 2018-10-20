#include "finish.h"
#include "ui_finish.h"

#include "window.h"

namespace webidl2cpp_application
{
    Finish::Finish(Window* window, QWidget * parent) :
        QDialog(parent),
        ui(new Ui::Finish),
        mWindow(window),
        mLog(0)
    {
        ui->setupUi(this);
        log().setReference(ui->log);

        connect(ui->close, SIGNAL(clicked()), this, SLOT(hide()));
        connect(ui->showcpp, SIGNAL(clicked()), this, SLOT(showSource()));
        connect(ui->showh, SIGNAL(clicked()), this, SLOT(showHeader()));
    }

    Window* Finish::window()
    {
        return mWindow;
    }
    Log& Finish::log()
    {
        return mLog;
    }

    void Finish::showHeader()
    {
        window()->showHeaderOutput();
    }
    void Finish::showSource()
    {
        window()->showSourceOutput();
    }

    Finish::~Finish()
    {
        delete ui;
    }
}
