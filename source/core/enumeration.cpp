#include "enumeration.h"
#include "function.h"
#include "idl.h"

namespace NewtooWebInterfaceMapper_core
{
    const char doubleSpace[] = "  ";

    Enumeration::Enumeration(IDL* aIdl, std::string decl)
        :Definition(ENUMERATION, aIdl), mIsTyped(false), mIdl(aIdl)
    {
        // Назначить дополнительные параметры
        std::string after = decl.substr(0, decl.find('{'));
        std::size_t extAttrEnd = after.find(']');
        std::string extAttrString;
        if(extAttrEnd != std::string::npos)
        {
            extAttrString = after.substr(1, extAttrEnd);
            decl.erase(0, extAttrEnd + 1);
        }

        // Удалить пробелы, чтобы правильно назначить название
        while(decl.find(' ') == 0)
            decl.erase(0, 1);

        if(decl.find("typed ") == 0)
        {
            mIsTyped = true;
            decl.erase(0, 6);
        }

        // Назначить название
        std::size_t nameIndex = decl.find(' ');
        nameIndex++;
        std::size_t openBracketIndex = decl.find('{');
        mEnumerationName = decl.substr(nameIndex, openBracketIndex - nameIndex);
        while(mEnumerationName[mEnumerationName.size() - 1] == ' ')
            mEnumerationName.erase(mEnumerationName.size() - 1);

        // Добавить содержимое

        std::size_t closeBracketIndex = decl.find('}');
        if(closeBracketIndex == std::string::npos)
            return;

        std::string inner = decl.substr(openBracketIndex + 1, closeBracketIndex - openBracketIndex - 1);

        while(inner.find(doubleSpace) != std::string::npos)
            inner = inner.replace(inner.find(doubleSpace), 2, "");

        convertInner(inner);
    }

    std::string Enumeration::serializeHeader()
    {
        if(!isTyped())
            return "enum " + mEnumerationName + "\n{\n" + mConvertedInner + "\n};\n\n";
        else
            return "enum class " + mEnumerationName + "\n{\n" + mConvertedInner + "\n};\n\n";
    }

    std::string& Enumeration::enumerationName()
    {
        return mEnumerationName;
    }

    void Enumeration::markdownItem(std::string& str)
    {
        while(str[0] == ' ')
            str.erase(0, 1);
        while(str[str.size() - 1] == ' ')
            str.erase(str.size() - 1, 1);

        if(str[0] == '"')
            str.erase(0, 1);
        else
        {
            mIdl->error(mIdl->invalidSyntaxError(str));
        }
        if(str[str.size() - 1] == '"')
            str.erase(str.size() - 1, 1);
        else
        {
            mIdl->error(mIdl->invalidSyntaxError(str));
        }

        while(str.find(' ') != std::string::npos)
            str = str.replace(str.find(' '), 1, "_");
    }

    void Enumeration::convertInner(std::string& inner)
    {
        std::vector<std::string> list;
        list.push_back(inner);
        Function::splitSequentialListString(list, &list.back());

        std::size_t lastItemIndex = list.size() - 1;

        for(unsigned i = 0; i < list.size(); i++)
        {
            std::string item = list[i];
            markdownItem(item);

            mConvertedInner += "    " + item;

            if(i != lastItemIndex)
                mConvertedInner += ",\n";
        }
    }

    bool Enumeration::isTyped() const
    {
        return mIsTyped;
    }
}
