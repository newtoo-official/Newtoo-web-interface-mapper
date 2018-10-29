#include "log.h"

#include <QDateTime>

namespace NewtooWebInterfaceMapper_application
{
    Log::Log(QPlainTextEdit* aReference)
        : mReference(aReference)
    {}

    char Log::newlineSign()
    {
        return '\n';
    }
    char Log::dateSplitter()
    {
        return '.';
    }
    char Log::timeSplitter()
    {
        return ':';
    }
    char Log::datetimeStart()
    {
        return '[';
    }
    char Log::datetimeEnd()
    {
        return ']';
    }
    char Log::splitter()
    {
        return ' ';
    }

    void Log::post(QString text)
    {
        QDateTime dateTime;

        std::string ptext;
        ptext += datetimeStart();
        ptext += std::to_string(dateTime.date().currentDate().day());
        ptext += dateSplitter();
        ptext += std::to_string(dateTime.date().currentDate().month());
        ptext += dateSplitter();
        ptext += std::to_string(dateTime.date().currentDate().year());
        ptext += splitter();
        ptext += std::to_string(dateTime.time().currentTime().hour());
        ptext += timeSplitter();
        ptext += std::to_string(dateTime.time().currentTime().minute());
        ptext += datetimeEnd();
        ptext += splitter();
        ptext += text.toStdString();

        mReference->appendPlainText(QString::fromStdString(ptext));
    }

    void Log::clear()
    {
        reference()->clear();
    }

    QPlainTextEdit* Log::reference() const
    {
        return mReference;
    }
    void Log::setReference(QPlainTextEdit* aReference)
    {
        mReference = aReference;
    }
}
