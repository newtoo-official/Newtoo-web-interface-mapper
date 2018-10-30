#include "extattrmap.h"
#include "function.h"
#include "iostream"

namespace NewtooWebInterfaceMapper_core
{

    const char closeArgBracket = ')';
    const char openArgBracket = '(';
    const char closeBracket = ']';
    const char openBracket = '[';
    const char splitter = ',';

    const char whitespace = ' ';

    ExtAttrMap::ExtAttrMap(std::string decl)
        : mNamedContructor(0),
          mConstructor(0),
          mCEReactions(0),
          mSameObject(0),
          mNewObject(0),
          mHasNamedContructor(false),
          mHasConstructor(false),
          mHasCEReactions(false),
          mHasSameObject(false),
          mHasNewObject(false)
    {
        std::vector<std::string> list;
        list.push_back(decl);
        Function::splitSequentialListString(list, &list[0]);

        for(unsigned i = 0; i < list.size(); i++)
        {
            std::string& extattr = list[i];

            while(extattr[0] == whitespace)
                extattr.erase(0, 1);

            if(extattr.find("NamedConstructor") == 0)
            {
                mList.push_back(ExtAttr(extattr, NAMED_CONSTRUCTOR_TYPE));
                mHasNamedContructor = true;
                mNamedContructor = i;
            }
            else if(extattr.find("Constructor") == 0)
            {
                mList.push_back(ExtAttr(extattr, CONSTRUCTOR_TYPE));
                mHasConstructor = true;
                mConstructor = i;
            }
            else if(extattr.find("CEReactions") == 0)
            {
                mList.push_back(ExtAttr(extattr, CEREACTIONS_TYPE));
                mHasCEReactions = true;
                mCEReactions = i;
            }
            else if(extattr.find("SameObject") == 0)
            {
                mList.push_back(ExtAttr(extattr, SAME_OBJECT_TYPE));
                mHasSameObject = true;
                mSameObject = i;
            }
            else if(extattr.find("NewObject") == 0)
            {
                mList.push_back(ExtAttr(extattr, NEW_OBJECT_TYPE));
                mHasNewObject = true;
                mNewObject = i;
            }
            else mList.push_back(ExtAttr(extattr, CUSTOM_TYPE));
        }
    }

    ExtAttr* ExtAttrMap::namedContructor()
    {
        if(!mHasNamedContructor)
            return 0;
        return &mList[mNamedContructor];
    }
    ExtAttr* ExtAttrMap::constructor()
    {
        if(!mHasConstructor)
            return 0;
        return &mList[mConstructor];
    }
    ExtAttr* ExtAttrMap::CEReactions()
    {
        if(!mHasCEReactions)
            return 0;
        return &mList[mCEReactions];
    }
    ExtAttr* ExtAttrMap::sameObject()
    {
        if(!mHasSameObject)
            return 0;
        return &mList[mSameObject];
    }
    ExtAttr* ExtAttrMap::newObject()
    {
        if(!mHasNewObject)
            return 0;
        return&mList[mNewObject];
    }

    std::vector<ExtAttr>& ExtAttrMap::list()
    {
        return mList;
    }
}
