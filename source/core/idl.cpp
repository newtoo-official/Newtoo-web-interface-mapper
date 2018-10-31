#include "idl.h"

namespace NewtooWebInterfaceMapper_core
{

    const char open_single_comment[] = "//";
    const char close_single_comment[] = "\n";
    const char open_comment[] = "/*";
    const char close_comment[] = "*/";

    void checkForCommentaries(std::string& ref)
    {
        if(ref.find(open_comment) == std::string::npos
                and ref.find(open_single_comment) == std::string::npos)
        return;

        std::string str = ref;

        while(str.find(open_comment) != std::string::npos
              and str.find(close_comment) != std::string::npos)
        {
            std::size_t start = str.find(open_comment);
            std::size_t end = str.find(close_comment);
            str.erase(start, end - start + 2);
        };
        while(str.find(open_single_comment) != std::string::npos
              and str.find(close_single_comment) != std::string::npos)
        {
            std::size_t start = str.find(open_single_comment);
            std::size_t end = str.find(close_single_comment, start);
            str.erase(start, end - start);
        };
        ref = str;
    }

    void replaceAll(std::string& subject, const std::string search, const std::string replace)
    {
        std::size_t pos = 0;
        while((pos = subject.find(search, pos)) != std::string::npos)
        {
             subject.replace(pos, search.length(), replace);
             pos += replace.length();
        }
    }

    std::string withNamespace(const std::string& str, std::string ns)
    {
        std::string ret = str;
        replaceAll(ret, "\n", "\n    ");
        ret = "namespace " + ns + "\n{\n    " + ret + "\n} // namespace " + ns;
        return ret;
    }

    IDL::IDL(std::string text, NewtooWebInterfaceMapper::Settings& settings)
        : mSettings(settings), mWarningCounter(0), mErrorCounter(0), mDefinitions(this),
          mOriginalText(text)
    {
        // Комментарии уже устарели и вышли из употребления, но всё равно следует удалить
        checkForCommentaries(text);

        DeclarationStringList list = declarationListFrom(text);

        for(unsigned i = 0; i < list.size(); i++)
            definitions().newDefinition(list[i]);

        serialize();

        if(settings.hasNamespace())
        {
            mHeader = withNamespace(mHeader, settings.getNamespace());
            mSource = withNamespace(mSource, settings.getNamespace());
        }

        mSource = mAboveSource + '\n' + mSource;
    }

    NewtooWebInterfaceMapper::Settings& IDL::settings()
    {
        return mSettings;
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
                        i++;
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

    std::string IDL::invalidSyntaxError(std::string fragment)
    {
        return "Invalid syntax" + atLineSuffix(fragment);
    }

    std::string IDL::atLineSuffix(std::string fragment)
    {
        return " at line " + std::to_string(getLine(fragment) + '.');
    }

    unsigned long IDL::getLine(std::string fragment)
    {
        std::size_t end = mOriginalText.find(fragment);
        if(end == std::string::npos)
            return FragmentNotFound;

        unsigned long amount = 1;

        for(unsigned i = 1; i < end; i++)
        {
            if(mOriginalText[i] == newline)
                amount++;
        }
        return amount;
    }

    void IDL::serialize()
    {
        definitions().cascade();
        definitions().serialize();
        alert("Finished with " + std::to_string(mWarningCounter) + " warnings and "
              + std::to_string(mErrorCounter) + " errors.");
    }

    std::string& IDL::header()
    {
        return mHeader;
    }
    std::string& IDL::source()
    {
        return mSource;
    }
    std::string& IDL::aboveSource()
    {
        return mAboveSource;
    }
    Log& IDL::log()
    {
        return mLog;
    }

    void IDL::alert(std::string message)
    {
        mLog.push_back(message);
    }

    void IDL::error(std::string message)
    {
        alert(ErrorPrefix + message);
        mErrorCounter++;
    }

    void IDL::warning(std::string message)
    {
        alert(WarningPrefix + message);
        mWarningCounter++;
    }

    DefinitionList& IDL::definitions()
    {
        return mDefinitions;
    }

    void IDL::removeSpaces(std::string& str)
    {
        while(str[0] == ' ')
            str.erase(0, 1);
        while(str[str.size() - 1] == ' ')
            str.erase(str.size() - 1, 1);
    }
}
