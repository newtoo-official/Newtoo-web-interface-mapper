#pragma once

#include "definition.h"
#include <vector>

namespace NewtooWebInterfaceMapper_core
{
    class Interface;
    class Dictionary;
    class Enumeration;

    class DefinitionList
    {
    public:
        DefinitionList(IDL* aIdl);
        ~DefinitionList();

        void newDefinition(std::string text);
        void serialize();
        void cascade();

        /* Ищет не частичные интерфейсы */
        Interface* findInterface(std::string name);
        Dictionary* findDictionary(std::string name);
        Enumeration* findEnumeration(std::string name);

        IDL* idl() const;

    private:
        std::vector<Definition*> mList;
        IDL* mIdl;
    };
}
