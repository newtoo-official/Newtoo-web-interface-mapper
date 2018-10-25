#include "definition.h"

namespace NewtooWebInterfaceMapper_core
{
    Definition::Definition(DefinitionType aType, IDL* aIdl, std::string decl)
        :mType(aType), mIdl(aIdl)
    {
        decl.clear();
    }

    Definition* Definition::create(std::string text, IDL* idl)
    {

    }

    DefinitionType Definition::type() const
    {
        return mType;
    }

    IDL* Definition::idl() const
    {
        return mIdl;
    }

    std::string Definition::serializeHeader()
    {
        return nullstr;
    }
    std::string Definition::serializeSource()
    {
        return nullstr;
    }
}
