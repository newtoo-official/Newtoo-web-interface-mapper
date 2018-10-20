#pragma once

#include <QPlainTextEdit>

namespace webidl2cpp_application
{
    class Log
    {
    public:
        Log(QPlainTextEdit* aReference);

        char newlineSign();
        char dateSplitter();
        char timeSplitter();
        char splitter();

        void post(QString text);
        void clear();

        QPlainTextEdit* reference() const;
        void setReference(QPlainTextEdit* aReference);

    private:

        QPlainTextEdit* mReference;
    };
}
