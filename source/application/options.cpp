#include "options.h"
#include "ui_options.h"

namespace NewtooWebInterfaceMapper_application
{
    Options::Options(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::Options)
    {
        ui->setupUi(this);

        ui->langField->addItem("English, US");

        connect(ui->cancel, SIGNAL(clicked()), this, SLOT(hide()));
        connect(ui->apply, SIGNAL(clicked()), this, SLOT(saveSettings()));
        connect(ui->ok, SIGNAL(clicked()), this, SLOT(saveAndClose()));
        connect(ui->restoreDefaults, SIGNAL(clicked()), this, SLOT(resetDefaults()));
    }

    NewtooWebInterfaceMapper::Settings& Options::settings()
    {
        return mSettings;
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
        ui->sequenceClassField->setText(QString::fromUtf8(mSettings.getSequence().c_str()));
        ui->timeStampClassField->setText(QString::fromUtf8(mSettings.getTimeStamp().c_str()));
        ui->exceptionOrVoidClassField->setText(QString::fromUtf8(mSettings.getExceptionOrVoid().c_str()));
        ui->arrayClassField->setText(QString::fromUtf8(mSettings.getArray().c_str()));
    }
    void Options::saveSettings()
    {
        mSettings.set(toUtf8(ui->namespaceField->text()),
                      toUtf8(ui->exceptionTemplateClassField->text()),
                      toUtf8(ui->stringPointerClassField->text()),
                      toUtf8(ui->langField->currentText()),
                      toUtf8(ui->sequenceClassField->text()),
                      toUtf8(ui->timeStampClassField->text()),
                      toUtf8(ui->exceptionOrVoidClassField->text()),
                      toUtf8(ui->arrayClassField->text()));
    }
    void Options::resetDefaults()
    {
        mSettings.resetDefaults();
        loadSettings();
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
