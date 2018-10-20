#include "log.h"

#include <QDateTime>

namespace webidl2cpp_application
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
    char Log::splitter()
    {
        return ' ';
    }

    void Log::post(QString text)
    {
        QDateTime dateTime;

        text.append(dateTime.date().currentDate().day());
        text.append(QChar::fromLatin1(dateSplitter()));
        text.append(dateTime.date().currentDate().month());
        text.append(QChar::fromLatin1(dateSplitter()));
        text.append(dateTime.date().currentDate().year());
        text.append(QChar::fromLatin1(splitter()));
        text.append(dateTime.time().currentTime().hour());
        text.append(QChar::fromLatin1(timeSplitter()));
        text.append(dateTime.time().currentTime().minute());
        text.append(QChar::fromLatin1(splitter()));
        text.append(text);
        text.append(QChar::fromLatin1(newlineSign()));
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
