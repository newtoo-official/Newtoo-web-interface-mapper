#pragma once

#include <QDialog>

namespace Ui
{
    class Output;
}
namespace NewtooWebInterfaceMapper_application
{
    class Output : public QDialog
    {
        Q_OBJECT

    public:
        explicit Output(QString title, QWidget *parent = 0);
        ~Output();

        void setText(std::string text);

    public slots:

        void copyToClipboard();

    private:
        Ui::Output *ui;
    };
}
