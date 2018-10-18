#include "output.h"
#include "ui_output.h"

namespace webidl2cpp_application
{
    Output::Output(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::Output)
    {
        ui->setupUi(this);
    }

    Output::~Output()
    {
        delete ui;
    }
}
