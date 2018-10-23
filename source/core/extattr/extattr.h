#pragma once

#include "string"

#define null 0

namespace webidl2cpp_core
{
    class IDefinition;
    class Object;

    class Extattr
    {
    public:
        enum ExtattrType
        {
            CONSTRUCTOR,
            NAMED_CONSTRUCTOR,
            SAME_OBJECT,
            NEW_OBJECT,
            CEREACTIONS,
            UNSCOPABLE,
            EXPOSED
        };
        Extattr(ExtattrType aType, Object* owner, std::string decl);
        ExtattrType type();

        Object* ownerObject();


    private:
        ExtattrType mType;
        Object* mOwnerObject;
    };
}
