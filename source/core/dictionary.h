#pragma once

#include "definition.h"

namespace NewtooWebInterfaceMapper_core
{
    class Dictionary : public Definition
    {
    public:
        Dictionary(IDL* aIdl, std::string decl);

        bool isPartial() const;

        std::string& dictionaryName();
        std::string& convertedTextWithDefaultValues();
        std::string& convertedText();
        std::string& toString(); // сокращение

    private:

        void inheritFrom(std::string name);

        std::string mDictionaryName;
        std::string mConvertedTextWithDefaultValues;
        std::string mConvertedText;
        bool mIsPartial;
    };
}
