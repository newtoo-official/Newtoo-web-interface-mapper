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
        virtual ~Definition();

        IDL* idl() const;

        static DefinitionType defineType(std::string decl);

        /*
            Тут какой-то странный баг с этими виртуальными функциями. Они не переназначаются.
        */

        virtual std::string serializeHeader();
        virtual std::string serializeSource();
        virtual void cascade();

        virtual void modifySource(std::string& source);
        /*
            Редактирование исходного кода по усмотрению класса.
            Например, интерфейс добавляет в исходники директиву #include
        */

    protected:

        DefinitionType mType;
        IDL* mIdl;
    };
}
