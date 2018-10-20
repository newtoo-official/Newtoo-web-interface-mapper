#include "about.h"
#include "ui_about.h"

namespace webidl2cpp_application
{
    About::About(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::About)
    {
        ui->setupUi(this);

        connect(ui->close, SIGNAL(clicked()), this, SLOT(hide()));
    }

    About::~About()
    {
        delete ui;
    }
}
