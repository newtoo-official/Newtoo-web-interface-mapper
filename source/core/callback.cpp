#include "callback.h"
#include "function.h"
#include "idl.h"

namespace NewtooWebInterfaceMapper_core
{
    Callback::Callback(IDL* aIdl, std::string decl)
        :Definition(CALLBACK_TYPE, aIdl)
    {
        // Вырезать дополнительные параметры
        std::size_t extAttrEnd = decl.find(']');
        if(extAttrEnd != std::string::npos)
            decl.erase(0, extAttrEnd + 1);
        while(decl[0] == ' ')
            decl.erase(0, 1);

        if(decl.find("callback ") == 0)
            decl.erase(0, 9);

        std::size_t splitter = decl.find('=');

        if(splitter == std::string::npos)
        {
            aIdl->error(aIdl->invalidSyntaxError(decl));
            return;
        }

        mCallbackName = decl.substr(0, splitter);
        IDL::removeSpaces(mCallbackName);

        std::string after = decl.substr(splitter + 1, decl.size() - splitter - 2);

        std::size_t openBracket = after.find_first_of('(');
        std::size_t closeBracket = after.find_last_of(')');

        if(openBracket == std::string::npos or closeBracket == std::string::npos)
        {
            aIdl->error(aIdl->invalidSyntaxError(decl));
            return;
        }

        mCallbackType = after.substr(0, openBracket);
        IDL::removeSpaces(mCallbackType);

        mCallbackType = Function::toC_StyleType(mCallbackType, aIdl);

        mArguments = Function::convertArguments(after.substr(openBracket + 1,
                                    closeBracket - openBracket - 1), aIdl);
    }

    std::string& Callback::callbackName()
    {
        return mCallbackName;
    }

    std::string Callback::toString(std::string identifer)
    {
        return mCallbackType + " (*" + identifer + ")(" + mArguments + ')';
    }
}
