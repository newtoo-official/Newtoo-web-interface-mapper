#include "definitionlist.h"
#include "idl.h"
#include "interface.h"

namespace NewtooWebInterfaceMapper_core
{
    DefinitionList::DefinitionList(IDL* aIdl)
        :mIdl(aIdl)
    {}

    DefinitionList::~DefinitionList()
    {
        for(unsigned i = 0; i < mList.size(); i++)
            delete mList[i];
    }

    void DefinitionList::newDefinition(std::string text)
    {
        switch(Definition::defineType(text))
        {
            case INTERFACE:
            {
                mList.push_back(new Interface(mIdl, text));
                break;
            }
            case DICTONARY:
            {
                break;
            }
            case ENUMERATION:
            {
                break;
            }
            case TYPEDEFINE:
            {
                break;
            }
            case IMPLEMENTS:
            {
                break;
            }
            case INCLUDES:
            {
                break;
            }
            case UNKNOWN_TYPE:
            {
                break;
            }
        }
    }

    void DefinitionList::serialize()
    {
        for(unsigned i = 0; i < mList.size(); i++)
            idl()->header() += mList[i]->serializeHeader();

        for(unsigned i = 0; i < mList.size(); i++)
            idl()->source() += mList[i]->serializeSource();
    }

    void DefinitionList::cascade()
    {
        for(unsigned i = 0; i < mList.size(); i++)
            mList[i]->cascade();
    }

    Interface* DefinitionList::findInterface(std::string name)
    {
        for(unsigned i = 0; i < mList.size(); i++)
        {
            if(mList[i]->type() != INTERFACE)
                continue;

            Interface* in = (Interface*)mList[i];

            if(in->interfaceName() == name)
                return in;
        }
        return 0;
    }

    Dictonary* DefinitionList::findDictonary(std::string name)
    {
        return 0;
    }

    IDL* DefinitionList::idl() const
    {
        return mIdl;
    }

}
