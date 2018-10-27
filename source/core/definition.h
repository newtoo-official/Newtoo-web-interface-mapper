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
        INCLUDES,
        UNKNOWN_TYPE
    };

    class Definition
    {
    public:
        Definition(DefinitionType aType, IDL* aIdl);
        DefinitionType type() const;

        IDL* idl() const;

        static DefinitionType defineType(std::string decl);

        /*
            Тут какой-то странный баг с этими виртуальными функциями. Они не переназначаются.
        */

        virtual std::string serializeHeader();
        virtual std::string serializeSource();
        virtual void cascade();

    protected:

        DefinitionType mType;
        IDL* mIdl;
    };
}
