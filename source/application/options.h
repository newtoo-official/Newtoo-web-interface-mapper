#pragma once

#include <QDialog>
#include "../shared/settings.h"

namespace Ui
{
    class Options;
}
namespace NewtooWebInterfaceMapper_application
{
    class Options : public QDialog
    {
        Q_OBJECT

    public:
        explicit Options(QWidget *parent = 0);
        ~Options();

        NewtooWebInterfaceMapper::Settings& settings();

    public slots:

        void loadSettings();
        void saveSettings();
        void resetDefaults();
        void saveAndClose();

    private:
        Ui::Options *ui;
        NewtooWebInterfaceMapper::Settings mSettings;
    };
}
