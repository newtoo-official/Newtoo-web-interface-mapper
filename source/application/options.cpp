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

    std::string toUtf8(QString str)
    {
        return std::string(str.toUtf8().constData());
    }

    void Options::loadSettings()
    {
        ui->namespaceField->setText(QString::fromUtf8(mSettings.getNamespace().c_str()));
        ui->exceptionTemplateClassField->setText(QString::fromUtf8(mSettings.getExceptionTemplateClass().c_str()));
        ui->stringPointerClassField->setText(QString::fromUtf8(mSettings.getStringPointerClass().c_str()));
        ui->langField->setCurrentText(QString::fromUtf8(mSettings.getInterfaceLanguage().c_str()));
    }
    void Options::saveSettings()
    {
        mSettings.set(toUtf8(ui->namespaceField->text()),
                      toUtf8(ui->exceptionTemplateClassField->text()),
                      toUtf8(ui->stringPointerClassField->text()),
                      toUtf8(ui->langField->currentText()));
    }
    void Options::resetDefaults()
    {
        mSettings.resetDefaults();
    }
    void Options::saveAndClose()
    {
        saveSettings();
        hide();
    }

    Options::~Options()
    {
        delete ui;
    }
}
