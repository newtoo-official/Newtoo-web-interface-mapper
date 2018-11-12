#pragma once

#include "definition.h"

namespace NewtooWebInterfaceMapper_core
{
    class Enumeration : public Definition
    {
    public:
        Enumeration(IDL* aIdl, std::string decl);

        std::string serializeHeader() override;

        std::string& enumerationName();

        bool isTyped() const;

    private:
        void convertInner(std::string& inner);
        void markdownItem(std::string& str);

        bool mIsTyped;
        std::string mEnumerationName;
        std::string mConvertedInner;
        IDL* mIdl;

        bool mUseGlobalEnumerations;
    };
}
