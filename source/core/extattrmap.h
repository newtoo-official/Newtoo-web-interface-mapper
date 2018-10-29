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

        std::vector<ExtAttr>& list();

    private:
        unsigned long mNamedContructor;
        unsigned long mConstructor;
        unsigned long mCEReactions;
        unsigned long mSameObject;
        unsigned long mNewObject;

        bool mHasNamedContructor;
        bool mHasConstructor;
        bool mHasCEReactions;
        bool mHasSameObject;
        bool mHasNewObject;

        std::vector<ExtAttr> mList;
    };
}
