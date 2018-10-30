#include "argument.h"
#include "function.h"
#include "idl.h"

namespace NewtooWebInterfaceMapper_core
{
    Argument::Argument(std::string decl, IDL* idl, bool isOptional)
        : mIsOptional(isOptional), mIsVaild(true)
    {
        std::size_t equalsSign = decl.find('=');
        std::string before = decl;
        if(equalsSign != std::string::npos)
        {
            mIsOptional = true;
            mDefaultValue = decl.substr(equalsSign + 1, decl.size() - equalsSign - 1);
            before = decl.substr(0, equalsSign);
        }

        std::size_t nameStart = before.find_last_of(' ');
        if(nameStart == std::string::npos)
        {
            //idl->error("Missing type or identifer"+idl->atLineSuffix(decl));
            mIsVaild = false;
            return;
        }

        Function::Type type = Function::typeFromString(before.substr(0, nameStart), idl);
        mType = type.text;

        mIdentifer = before.substr(nameStart + 1, before.size() - nameStart - 1);

        if(equalsSign == std::string::npos and mIsOptional)
        {
            if(type.isStringType)
                mDefaultValue = "\"\"";
            else
                mDefaultValue = "0";
        }
    }

    std::string& Argument::type()
    {
        return mType;
    }
    std::string& Argument::identifer()
    {
        return mIdentifer;
    }

    std::string& Argument::defaultValue()
    {
        return mDefaultValue;
    }

    std::string Argument::toString()
    {
        if(isOptional())
            return mType + ' ' + mIdentifer + " = " + mDefaultValue;
        else
        {
            return mType + ' ' + mIdentifer;
        }
    }

    bool Argument::isOptional() const
    {
        return mIsOptional;
    }
    bool Argument::isValid() const
    {
        return mIsVaild;
    }
}
