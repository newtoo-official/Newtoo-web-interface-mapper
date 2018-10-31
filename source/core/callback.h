#pragma once

#include "definition.h"

namespace NewtooWebInterfaceMapper_core
{
    class Callback : public Definition
    {
    public:
        Callback(IDL* aIdl, std::string decl);

        std::string& callbackName();

        std::string toString(std::string identifer);

    private:
        std::string mCallbackName;
        std::string mCallbackType;
        std::string mArguments;
    };
}
