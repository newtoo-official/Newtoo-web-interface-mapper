#pragma once

#include <QPlainTextEdit>
#include <QDialog>
#include "log.h"

namespace Ui
{
    class Finish;
}
namespace NewtooWebInterfaceMapper_application
{
    class Window;

    enum FinishType
    {
        CONVERTED_AND_SAVED,
        CONVERTED,
        INITIAL
    };

    class Finish : public QDialog
    {
        Q_OBJECT

    public:
        explicit Finish(Window* window, QWidget *parent = 0);
        ~Finish();

        FinishType type() const;
        void setType(FinishType aType);

        Window* window();
        Log& log();

    public slots:

        void showHeader();
        void showSource();

    private:

        void updateControls();

        Ui::Finish *ui;

        FinishType mType;
        Window* mWindow;
        Log mLog;
    };
}
