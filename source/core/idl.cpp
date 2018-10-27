#include "idl.h"

namespace NewtooWebInterfaceMapper_core
{

    IDL::IDL(std::string text, NewtooWebInterfaceMapper::Settings& settings)
        : mSettings(settings), mErrorCounter(0), mDefinitions(this)
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

    const char tab = '	';
    const char whitespace = ' ';
    const char newline = '\n';

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

        for(unsigned i = 0; i < list.size(); i++)
        {
            std::string& dec = list[i];

            while(dec[0] == whitespace)
                dec.erase(0, 1);
            while(dec[dec.size() - 1] == whitespace)
                dec.erase(dec.size() - 1, 1);

            while(dec.find(newline) != std::string::npos)
                dec = dec.replace(dec.find(newline), 1, "");

            while(dec.find(tab) != std::string::npos)
                dec = dec.replace(dec.find(tab), 1, "");
        }
        return list;
    }

    void IDL::serialize()
    {
        definitions().cascade();
        definitions().serialize();
        log().push_back("Finished with " + std::to_string(mErrorCounter) + " errors.");
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

    void IDL::error(std::string text)
    {
        log().push_back(text);
        mErrorCounter++;
    }

    DefinitionList& IDL::definitions()
    {
        return mDefinitions;
    }
}
