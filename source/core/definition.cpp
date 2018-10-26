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
    void Definition::cascade()
    {

    }

    std::string& Definition::copyConstructorStart()
    {
        return mCopyConstructorStart;
    }
    std::string& Definition::copyConstructorInitFields()
    {
        return mCopyConstructorInitFields;
    }
    std::string& Definition::copyConstructorEnd()
    {
        return mCopyConstructorEnd;
    }
    std::string& Definition::headerStart()
    {
        return mHeaderStart;
    }
    std::string& Definition::headerInherit()
    {
        return mHeaderInherit;
    }
    std::string& Definition::headerPublic()
    {
        return mHeaderPublic;
    }
    std::string& Definition::headerPublicAppendix()
    {
        return mHeaderPublicAppendix;
    }
    std::string& Definition::headerPrivate()
    {
        return mHeaderPrivate;
    }
    std::string& Definition::headerEnd()
    {
        return mHeaderEnd;
    }
    std::string& Definition::source()
    {
        return mSource;
    }
}
