#pragma once

#include <QDialog>

namespace Ui
{
    class Output;
}
namespace webidl2cpp_application
{
    class Output : public QDialog
    {
        Q_OBJECT

    public:
        explicit Output(QWidget *parent = 0);
        ~Output();

    private:
        Ui::Output *ui;
    };
}
