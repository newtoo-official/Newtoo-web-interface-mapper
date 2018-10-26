#include "idl.h"

namespace NewtooWebInterfaceMapper_core
{

    IDL::IDL(std::string text, NewtooWebInterfaceMapper::Settings& settings)
        : mDefinitions(this), mSettings(settings)
    {
        DeclarationStringList list = declarationListFrom(text);

        for(unsigned i = 0; i < list.size(); i++)
            definitions().newDefinition(list[i]);

        serialize();
    }

    const char quote_char = '\"';
    const char alternative_quote = '\'';
    const char close_rule = '}';
    const char close_single_rule = ';';
    const char open_rule = '{';

    #define split_target() \
    list.push_back(target->substr(i + 1, target->size() - i - 1)); \
    target = &list[list.size() - 2]; \
    target->erase(i + 1, target->size() - i - 1); \
    target = &list.back(); \
    size = target->size(); \
    i = 0; continue

    DeclarationStringList IDL::declarationListFrom(std::string str)
    {
        DeclarationStringList list;
        list.push_back(str);

        std::string* target = &list[0];

        unsigned long size, level, i;
        size = target->size();
        level = 0;
        i = 0;

        bool inquotes = false;
        char quote = 0;

        while(true)
        {
            if(i >= size)
                break;

            if(!inquotes)
            {
                switch(target->at(i))
                {
                    default:
                    {
                        i++;
                        break;
                    }
                    case open_rule:
                    {
                        level++;
                        i++;
                        break;
                    }
                    case close_rule:
                    {
                        level--;
                        if(level == 0)
                        {
                            split_target();
                        }
                        else i++;
                        break;
                    }
                    case close_single_rule:
                    {
                        if(level == 0)
                        {
                            split_target();
                        }
                        else i++;
                        break;
                    }
                    case quote_char:
                    {
                        inquotes = true;
                        quote = quote_char;
                        i++;
                        break;
                    }
                    case alternative_quote:
                    {
                        inquotes = true;
                        quote = alternative_quote;
                        i++;
                        break;
                    }
                }
            } else
            {
                if(target->at(i) == quote)
                    inquotes = false;
                i++;
            }
        }

        list.pop_back(); // Удалить пустую строку

        return list;
    }

    void IDL::serialize()
    {
        header() = "Hello!";
        source() = "Goodbie!";
        log().push_back("Please note, that this is only test conversion");
        log().push_back("Successful generated hello!");
    }

    std::string& IDL::header()
    {
        return mHeader;
    }
    std::string& IDL::source()
    {
        return mSource;
    }
    Log& IDL::log()
    {
        return mLog;
    }

    DefinitionList& IDL::definitions()
    {
        return mDefinitions;
    }
}
