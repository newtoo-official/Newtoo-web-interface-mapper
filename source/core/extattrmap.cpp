#include "extattrmap.h"
#include "iostream"

namespace NewtooWebInterfaceMapper_core
{

    const char closeArgBracket = ')';
    const char openArgBracket = '(';
    const char closeBracket = ']';
    const char openBracket = '[';
    const char splitter = ',';

    void split(std::vector<std::string>& list, std::string* target)
    {
        std::size_t splitterIndex;
        bool inBrackets = false;

        bool found = false;
        for(unsigned i = 0; i < target->size(); i++)
        {
            char c = target->at(i);
            if(!inBrackets)
            {
                if(c == openArgBracket)
                {
                    inBrackets = true;
                }
                else if(c == splitter)
                {
                    splitterIndex = i;
                    found = true;
                    break;
                }
            } else
            {
                if(c == closeArgBracket)
                    inBrackets = false;
            }
        }

        if(!found)
            return;

        std::string next = target->substr(splitterIndex + 1, target->size() - splitterIndex - 1);
        *target = target->substr(0, splitterIndex + 1);
        list.push_back(next);
        split(list, &list.back());
    }

    const char whitespace = ' ';

    ExtAttrMap::ExtAttrMap(std::string decl)
        : mNamedContructor(0),
          mConstructor(0),
          mCEReactions(0),
          mSameObject(0),
          mNewObject(0)
    {
        std::vector<std::string> list;
        list.push_back(decl);
        split(list, &list[0]);

        for(unsigned i = 0; i < list.size(); i++)
        {
            std::string& extattr = list[i];

            while(extattr[0] == whitespace)
                extattr.erase(0, 1);

            if(extattr.find("NamedConstructor") == 0)
            {
                mList.push_back(ExtAttr(extattr, NAMED_CONSTRUCTOR_TYPE));
                mNamedContructor = i;
            }
            else if(extattr.find("Constructor") == 0)
            {
                mList.push_back(ExtAttr(extattr, CONSTRUCTOR_TYPE));
                mConstructor = i;
            }
            else if(extattr.find("CEReactions") == 0)
            {
                mList.push_back(ExtAttr(extattr, CEREACTIONS_TYPE));
                mCEReactions = i;
            }
            else if(extattr.find("SameObject") == 0)
            {
                mList.push_back(ExtAttr(extattr, SAME_OBJECT_TYPE));
                mSameObject = i;
            }
            else if(extattr.find("NewObject") == 0)
            {
                mList.push_back(ExtAttr(extattr, NEW_OBJECT_TYPE));
                mNewObject = i;
            }
            else mList.push_back(ExtAttr(extattr, CUSTOM_TYPE));
        }
    }

    ExtAttr* ExtAttrMap::namedContructor()
    {
        return &mList[mNamedContructor];
    }
    ExtAttr* ExtAttrMap::constructor()
    {
        return &mList[mConstructor];
    }
    ExtAttr* ExtAttrMap::CEReactions()
    {
        return &mList[mCEReactions];
    }
    ExtAttr* ExtAttrMap::sameObject()
    {
        return &mList[mSameObject];
    }
    ExtAttr* ExtAttrMap::newObject()
    {
        return&mList[mNewObject];
    }

    std::vector<ExtAttr>& ExtAttrMap::list()
    {
        return mList;
    }
}
