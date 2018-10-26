#include "finish.h"
#include "ui_finish.h"

#include "window.h"

namespace NewtooWebInterfaceMapper_application
{
    Finish::Finish(Window* window, QWidget * parent) :
        QDialog(parent),
        ui(new Ui::Finish),
        mType(INITIAL),
        mWindow(window),
        mLog(0)
    {
        ui->setupUi(this);
        log().setReference(ui->log);

        connect(ui->close, SIGNAL(clicked()), this, SLOT(hide()));
        connect(ui->showcpp, SIGNAL(clicked()), this, SLOT(showSource()));
        connect(ui->showh, SIGNAL(clicked()), this, SLOT(showHeader()));

        updateControls();
    }

    FinishType Finish::type() const
    {
        return mType;
    }
    void Finish::setType(FinishType aType)
    {
        mType = aType;
        window()->headerOutput()->hide();
        window()->sourceOutput()->hide();
        updateControls();
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

    void Finish::updateControls()
    {
        switch(type())
        {
            case CONVERTED_AND_SAVED:
            {
                ui->showcpp->setDisabled(true);
                ui->showh->setDisabled(true);
                ui->openfolder->setDisabled(false);
                break;
            }
            case CONVERTED:
            {
                ui->showcpp->setDisabled(false);
                ui->showh->setDisabled(false);
                ui->openfolder->setDisabled(true);
                break;
            }
            case INITIAL:
            {
                ui->showcpp->setDisabled(true);
                ui->showh->setDisabled(true);
                ui->openfolder->setDisabled(true);
                break;
            }
        }
    }

    Finish::~Finish()
    {
        delete ui;
    }
}
