#include "extattrmap.h"

namespace NewtooWebInterfaceMapper_core
{

    const char closeBracket = ']';
    const char openBracket = '[';
    const char splitter = ',';

    void split(std::vector<std::string>& list, std::string* target)
    {
        std::size_t splitterIndex = target->find(splitter);
        if(splitterIndex == std::string::npos)
            return;

        list.push_back(target->substr(splitterIndex + 1, target->size() - splitterIndex - 1));
        *target = target->substr(0, splitterIndex);
        split(list, &list.back());
    }

    ExtAttrMap::ExtAttrMap(std::string decl)
    {
        std::vector<std::string> list;
        list.push_back(decl);
        split(list, &list[0]);

        for(unsigned i = 0; i < list.size(); i++)
        {
            std::string& extattr = list[i];

            mList.push_back(ExtAttr(extattr));

            if(extattr.find("NamedConstructor") == 0)
                mNamedContructor = &mList.back();
            else if(extattr.find("Constructor") == 0)
                mConstructor = &mList.back();
            else if(extattr.find("CEReactions") == 0)
                mCEReactions = &mList.back();
            else if(extattr.find("SameObject") == 0)
                mSameObject = &mList.back();
            else if(extattr.find("NewObject") == 0)
                mNewObject = &mList.back();
        }
    }

    ExtAttr* ExtAttrMap::namedContructor()
    {
        return mNamedContructor;
    }
    ExtAttr* ExtAttrMap::constructor()
    {
        return mConstructor;
    }
    ExtAttr* ExtAttrMap::CEReactions()
    {
        return mCEReactions;
    }
    ExtAttr* ExtAttrMap::sameObject()
    {
        return mSameObject;
    }
    ExtAttr* ExtAttrMap::newObject()
    {
        return mNewObject;
    }
}
