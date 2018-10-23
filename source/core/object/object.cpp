#include "object.h"

namespace webidl2cpp_core
{
    Object::Object(ObjectType oType, IDefinition* idef, std::string decl)
    {

    }

    std::string Object::serializePublic()
    {
        return nullstr;
    }

    std::string Object::serializePrivate()
    {
        return nullstr;
    }

    std::string Object::serializeSource()
    {
        return nullstr;
    }

    std::string Object::serializeInheritance()
    {
        return nullstr;
    }

    std::string Object::serializeCopy()
    {
        return nullstr;
    }
}
