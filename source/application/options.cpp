#include "options.h"
#include "ui_options.h"

namespace webidl2cpp_application
{
    Options::Options(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::Options)
    {
        ui->setupUi(this);
    }

    Options::~Options()
    {
        delete ui;
    }
}
