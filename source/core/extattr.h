#pragma once

#include <string>

namespace NewtooWebInterfaceMapper_core
{

    enum ExtAttrType
    {
        NAMED_CONSTRUCTOR_TYPE,
        CONSTRUCTOR_TYPE,
        CEREACTIONS_TYPE,
        SAME_OBJECT_TYPE,
        NEW_OBJECT_TYPE,
        CUSTOM_TYPE
    };

    class ExtAttr
    {
    public:
        ExtAttr(std::string expression, const ExtAttrType aType);

        ExtAttrType type();

        std::string& name();
        std::string& value();

    private:
        ExtAttrType mType;
        std::string mName;
        std::string mValue;
    };
}
