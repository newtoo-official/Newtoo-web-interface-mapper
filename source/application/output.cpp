#include "output.h"
#include "ui_output.h"

#include <QClipboard>

namespace NewtooWebInterfaceMapper_application
{
    Output::Output(QString title, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::Output)
    {
        ui->setupUi(this);
        setWindowTitle(title);

        connect(ui->copy, SIGNAL(clicked()), this, SLOT(copyToClipboard()));
        connect(ui->close, SIGNAL(clicked()), this, SLOT(hide()));
    }

    void Output::copyToClipboard()
    {
        QApplication::clipboard()->setText(ui->text->toPlainText());
    }

    Output::~Output()
    {
        delete ui;
    }
}
