#include "dictionaryunit.h"
#include "idl.h"

namespace NewtooWebInterfaceMapper_core
{
    DictionaryUnit::DictionaryUnit(std::string decl, IDL* idl)
        : mUnitType(UNIT_NORMAL), mIsStringType(false)
    {
        while(decl[0] == ' ')
            decl.erase(0, 1);
        while(decl[decl.size() - 1] == ' ')
            decl.erase(decl.size() - 1, 1);

        std::size_t identiferStart;

        if(decl.find("required ") == 0)
        {
            mUnitType = UNIT_REQUIRED;
            decl.erase(0, 9);
        }
        else if(decl.find("optional ") == 0)
        {
            mUnitType = UNIT_OPTIONAL;
            decl.erase(0, 9);
        }

        std::size_t equalsSignIndex = decl.find(" = ");

        std::string before;

        if(equalsSignIndex != std::string::npos)
        {
            before = decl.substr(0, equalsSignIndex);
            mDefaultValue = decl.substr(equalsSignIndex + 3, decl.size() - equalsSignIndex - 3);
        } else
        {
            before = decl;
        }

        identiferStart = before.find_last_of(' ');

        if(identiferStart == std::string::npos)
        {
            mUnitType = UNIT_INVALID;
            idl->error(idl->invalidSyntaxError(decl));
            return;
        }

        std::string typeidl = before.substr(0, identiferStart);
        IDL::removeSpaces(typeidl);

        Function::Type type = Function::typeFromString(typeidl, idl);
        mType = type.text;

        if(mType[mType.size() - 1] == '&')
            mType.erase(mType.size() - 1, 1);

        mIsStringType = type.isStringType;

        mIdentifer = before.substr(identiferStart + 1, before.size() - identiferStart - 1);
        IDL::removeSpaces(mIdentifer);

        if(equalsSignIndex != std::string::npos)
        {
            if(mUnitType == UNIT_REQUIRED)
            {
                idl->warning("Required member cannot have a default value"
                               + idl->atLineSuffix("required "+decl));
            }
        } else
        {
            if(type.isStringType)
                mDefaultValue = "\"\"";
            else
                mDefaultValue = "0";
        }
    }

    DictionaryUnitType DictionaryUnit::unitType() const
    {
        return mUnitType;
    }

    std::string& DictionaryUnit::type()
    {
        return mType;
    }
    std::string& DictionaryUnit::identifer()
    {
        return mIdentifer;
    }
    std::string& DictionaryUnit::defaultValue()
    {
        return mDefaultValue;
    }

    std::string DictionaryUnit::toStringWithDefaultValue()
    {
        return mType + ' ' + mIdentifer + " = " + mDefaultValue;
    }

    std::string DictionaryUnit::toString()
    {
        std::string ret = mType + ' ' + mIdentifer;

        if(mUnitType == UNIT_OPTIONAL)
            ret += " = " + mDefaultValue;

        return ret;
    }
}
