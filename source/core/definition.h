#pragma once

#include <string>

#define nullstr ""

namespace NewtooWebInterfaceMapper_core
{
    class IDL;

    enum DefinitionType
    {
        INTERFACE,
        DICTONARY,
        ENUMERATION,
        TYPEDEFINE,
        IMPLEMENTS,
        INCLUDES
    };

    class Definition
    {
    public:
        Definition* create(std::string text, IDL* idl);
        DefinitionType type() const;

        IDL* idl() const;

        virtual std::string serializeHeader();
        virtual std::string serializeSource();

    protected:
        Definition(DefinitionType aType, IDL* aIdl, std::string decl);

    private:
        DefinitionType mType;
        IDL* mIdl;
    };
}
