#pragma once

#include <QDialog>
#include "../shared/settings.h"

namespace Ui
{
    class Options;
}
namespace webidl2cpp_application
{
    class Options : public QDialog
    {
        Q_OBJECT

    public:
        explicit Options(QWidget *parent = 0);
        ~Options();

    public slots:

        void loadSettings();
        void saveSettings();
        void resetDefaults();
        void saveAndClose();

    private:
        Ui::Options *ui;
        webidl2cpp::Settings mSettings;
    };
}
