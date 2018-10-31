#include "dictionary.h"
#include "function.h"
#include "idl.h"
#include "dictionaryunit.h"

namespace NewtooWebInterfaceMapper_core
{
    const char splitter = ';';

    void splitMembers(std::vector<std::string>& list, std::string* target)
    {
        std::size_t splitterIndex;

        bool found = false;
        for(unsigned i = 0; i < target->size(); i++)
        {
            if(target->at(i) == splitter)
            {
                splitterIndex = i;
                found = true;
                break;
            }
        }

        if(!found)
            return;

        std::string next = target->substr(splitterIndex + 1, target->size() - splitterIndex - 1);
        *target = target->substr(0, splitterIndex);
        list.push_back(next);
        splitMembers(list, &list.back());
    }

    const char doubleSpace[] = "  ";

    Dictionary::Dictionary(IDL* aIdl, std::string decl)
        :Definition(DICTIONARY, aIdl), mIsPartial(false)
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

        if(after.find("partial ") == 0)
        {
            mIsPartial = true;
            decl.erase(0, 9);
        }

        // Назначить название
        std::size_t nameIndex = decl.find(' ');
        nameIndex++;
        std::size_t inheritsIndex = decl.find(':');
        std::size_t openBracketIndex = decl.find('{');
        if(inheritsIndex == std::string::npos)
            mDictionaryName = decl.substr(nameIndex, openBracketIndex - nameIndex);
        else
        {
            mDictionaryName = decl.substr(nameIndex, inheritsIndex - nameIndex);
        }
        while(mDictionaryName[mDictionaryName.size() - 1] == ' ')
            mDictionaryName.erase(mDictionaryName.size() - 1);

        // Назначить наследование
        if(inheritsIndex != std::string::npos)
        {
            std::string inherits = decl.substr(inheritsIndex + 1, openBracketIndex - inheritsIndex - 1);

            while(inherits.find(' ') != std::string::npos)
                inherits = inherits.replace(inherits.find(' '), 1, "");

            inheritFrom(inherits);
        }

        // Добавить содержимое

        std::size_t closeBracketIndex = decl.find('}');
        if(closeBracketIndex == std::string::npos)
            return;

        std::string inner = decl.substr(openBracketIndex + 1, closeBracketIndex - openBracketIndex - 1);

        while(inner.find(doubleSpace) != std::string::npos)
            inner = inner.replace(inner.find(doubleSpace), 2, "");

        std::vector<std::string> list;
        list.push_back(inner);
        splitMembers(list, &list.back());

        // Удалить пустую строку
        list.pop_back();

        for(unsigned i = 0; i < list.size(); i++)
        {
            if(i > 0)
            {
                mConvertedTextWithDefaultValues += ", ";
                mConvertedText += ", ";
            }

            DictionaryUnit unit(list[i], aIdl);

            mConvertedTextWithDefaultValues += unit.toStringWithDefaultValue();
            mConvertedText += unit.toString();
        }

        // Каскадинг

        if(!isPartial())
            return;

        Dictionary* reference = idl()->definitions().findDictionary(mDictionaryName);
        if(reference != 0)
        {
            reference->convertedTextWithDefaultValues() += ", " + mConvertedTextWithDefaultValues;
            reference->convertedText() += ", " + mConvertedText;
        } else
        {
            idl()->warning("dictionary \"" + mDictionaryName + "\" doesn't exists"
                           + idl()->atLineSuffix("partial dictionary " + mDictionaryName));
        }
    }

    void Dictionary::cascade()
    {

    }

    bool Dictionary::isPartial() const
    {
        return mIsPartial;
    }

    std::string& Dictionary::dictionaryName()
    {
        return mDictionaryName;
    }

    std::string& Dictionary::convertedTextWithDefaultValues()
    {
        return mConvertedTextWithDefaultValues;
    }

    std::string& Dictionary::convertedText()
    {
        return mConvertedText;
    }

    std::string& Dictionary::toString()
    {
        return convertedText();
    }

    void Dictionary::inheritFrom(std::string name)
    {
        Dictionary* reference = idl()->definitions().findDictionary(name);
        if(reference != 0)
        {
            mConvertedTextWithDefaultValues = reference->convertedTextWithDefaultValues() + ", "
                    + mConvertedTextWithDefaultValues;

            mConvertedText = reference->convertedText() + ", " + mConvertedText;
        } else
        {
            idl()->warning("dictionary \"" + name + "\" doesn't exists"
                           + idl()->atLineSuffix("partial dictionary " + name)
                           + " Firstly define the dictionary before inheriting.");
        }
    }
}
