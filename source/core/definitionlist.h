#pragma once

#include "definition.h"
#include <vector>

namespace NewtooWebInterfaceMapper_core
{
    class Interface;
    class Dictonary;

    class DefinitionList
    {
    public:
        DefinitionList(IDL* aIdl);

        void newDefinition(std::string text);
        void serialize();
        void cascade();

        /* Ищет не частичные интерфейсы */
        Interface* findInterface(std::string name);
        Dictonary* findDictonary(std::string name);

        IDL* idl() const;

    private:
        std::vector<Definition> mList;
        IDL* mIdl;
    };
}
