#include "definitionlist.h"

namespace NewtooWebInterfaceMapper_core
{
    DefinitionList::DefinitionList(IDL* aIdl)
        :mIdl(aIdl)
    {}

    void DefinitionList::newDefinition(std::string text)
    {

    }

    void DefinitionList::serialize()
    {

    }

    void DefinitionList::cascade()
    {

    }

    Interface* DefinitionList::findInterface(std::string name)
    {
        return 0;
    }

    Dictonary* DefinitionList::findDictonary(std::string name)
    {
        return 0;
    }

    IDL* DefinitionList::idl() const
    {
        return mIdl;
    }

}
