#pragma once

#include <string>

namespace NewtooWebInterfaceMapper_core
{
    class IDL;

    enum DefinitionType
    {
        INTERFACE,
        DICTONARY,
        ENUMERATION,
        TYPEDEFINE,
        INCLUDES
    };

    class Definition
    {
    public:
        Definition(IDL* idl, std::string decl);
        DefinitionType type();

    private:
        DefinitionType mType;
    };
}
