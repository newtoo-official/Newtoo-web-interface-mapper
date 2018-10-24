#pragma once

#include <QPlainTextEdit>

namespace NewtooWebInterfaceMapper_application
{
    class Log
    {
    public:
        Log(QPlainTextEdit* aReference);

        char newlineSign();
        char dateSplitter();
        char timeSplitter();
        char datetimeStart();
        char datetimeEnd();
        char splitter();

        void post(QString text);
        void clear();

        QPlainTextEdit* reference() const;
        void setReference(QPlainTextEdit* aReference);

    private:

        QPlainTextEdit* mReference;
    };
}
