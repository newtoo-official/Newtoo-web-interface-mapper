#pragma once

#include "string"

#define nullstr ""
#define null 0

namespace webidl2cpp_core
{

    class Collection;
    class ExtattrList;
    class IDefinition;

    class Object
    {
    public:
        enum ObjectType
        {
            INTERFACE,
            ATTRIBUTE,
            ENUMERATION,
            LIST_ITEM,
            DICTONARY,
            TYPEDEFINE
        };
        Object(ObjectType oType, IDefinition* idef, std::string decl);
        ObjectType objectType();

        Object* owner() const;

        ExtattrList& extattrs();
        Collection& childs();

        virtual std::string serializePublic();
        virtual std::string serializePrivate();
        virtual std::string serializeSource();
        virtual std::string serializeInheritance();
        virtual std::string serializeCopy();

    private:
        IDefinition* mIDef;

        ObjectType mObjectType;
        Object* mOwner;

        //ExtattrList mExtattrs;
        //Collection mChilds;

    };
}
