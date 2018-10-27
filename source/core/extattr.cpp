#include "extattr.h"
namespace NewtooWebInterfaceMapper_core
{

    const char splitterSign = '=';

    ExtAttr::ExtAttr(std::string expression)
    {
        std::size_t indexOfSplitterSign = expression.find(splitterSign);

        if(indexOfSplitterSign != std::string::npos)
        {
            mName = expression.substr(0, indexOfSplitterSign);
            mValue = expression.substr(indexOfSplitterSign, expression.size() - indexOfSplitterSign);
        } else
        {
            mName = expression;
        }
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
