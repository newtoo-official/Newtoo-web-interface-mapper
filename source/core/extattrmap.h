#pragma once

#include "extattr.h"
#include <vector>

namespace NewtooWebInterfaceMapper_core
{
    class ExtAttrMap
    {
    public:
        ExtAttrMap(std::string decl);

        ExtAttr* namedContructor();
        ExtAttr* constructor();
        ExtAttr* CEReactions();
        ExtAttr* sameObject();
        ExtAttr* newObject();

    private:
        ExtAttr* mNamedContructor;
        ExtAttr* mConstructor;
        ExtAttr* mCEReactions;
        ExtAttr* mSameObject;
        ExtAttr* mNewObject;

        std::vector<ExtAttr> mList;
    };
}
