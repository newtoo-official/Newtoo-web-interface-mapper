#pragma once

#include <string>

namespace NewtooWebInterfaceMapper_core
{
    class ExtAttr
    {
    public:
        ExtAttr(std::string expression);

        std::string& name();
        std::string& value();

    private:
        std::string mName;
        std::string mValue;
    };
}
