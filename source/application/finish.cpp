#include "finish.h"
#include "ui_finish.h"

namespace webidl2cpp_application
{
    Finish::Finish(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::Finish)
    {
        ui->setupUi(this);
    }

    Finish::~Finish()
    {
        delete ui;
    }
}
