#pragma once

#include <QDialog>

namespace Ui
{
    class About;
}
namespace webidl2cpp_application
{
    class About : public QDialog
    {
        Q_OBJECT

    public:
        explicit About(QWidget *parent = 0);
        ~About();

    private:
        Ui::About *ui;
    };
}
