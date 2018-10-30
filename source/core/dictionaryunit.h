#pragma once

#include "dictionary.h"
#include "function.h"

namespace NewtooWebInterfaceMapper_core
{
    enum DictionaryUnitType
    {
        UNIT_REQUIRED,
        UNIT_OPTIONAL,
        UNIT_NORMAL,
        UNIT_INVALID
    };

    class DictionaryUnit
    {
    public:
        DictionaryUnit(std::string decl, IDL* idl);

        DictionaryUnitType unitType() const;

        std::string& type();
        std::string& identifer();
        std::string& defaultValue();

        std::string toStringWithDefaultValue();
        std::string toString();

    private:
        DictionaryUnitType mUnitType;

        bool mIsStringType;

        std::string mType;
        std::string mIdentifer;
        std::string mDefaultValue;
    };
}
