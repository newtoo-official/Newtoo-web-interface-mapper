#include "extattr.h"
namespace NewtooWebInterfaceMapper_core
{

    const char splitterSign = '=';

    ExtAttr::ExtAttr(std::string expression, const ExtAttrType aType)
        : mType(aType)
    {
        std::size_t indexOfSplitterSign = expression.find(splitterSign);

        if(indexOfSplitterSign != std::string::npos)
        {
            mName = expression.substr(0, indexOfSplitterSign);
            mValue = expression.substr(indexOfSplitterSign + 1, expression.size() - indexOfSplitterSign - 1);
        } else
        {
            mName = expression;
        }
    }

    ExtAttrType ExtAttr::type()
    {
        return mType;
    }

    std::string& ExtAttr::name()
    {
        return mName;
    }
    std::string& ExtAttr::value()
    {
        return mValue;
    }
}
