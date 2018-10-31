#pragma once

#include <string>

namespace NewtooWebInterfaceMapper_core
{
    class IDL;

    class Argument
    {
    public:
        Argument(std::string decl, IDL* idl, bool isOptional = false);

        std::string& type();
        std::string& identifer();

        std::string& defaultValue();

        std::string toString();

        bool isOptional() const;
        bool isValid() const;

    private:
        std::string mType;
        std::string mIdentifer;
        std::string mDefaultValue;

        std::string mAlternativeText;

        bool mIsOptional;
        bool mIsVaild;
    };
}
