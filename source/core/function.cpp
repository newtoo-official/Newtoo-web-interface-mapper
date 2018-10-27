#include "function.h"
#include "interface.h"
#include "idl.h"

namespace NewtooWebInterfaceMapper_core
{

    const char pointerSignCpp = '*';
    const char pointerSign = '?';

    const char referenceSuffix = '&';

    std::string Function::toC_StyleType(std::string& type)
    {
        if(type == "byte")
            return "signed char";
        if(type == "ocetet")
            return "unsigned char";
        if(type == "short")
            return "short";
        if(type == "unsigned short")
            return "unsigned short";
        if(type == "long")
            return "long";
        if(type == "unsigned long")
            return "unsigned long";
        if(type == "float")
            return "float";
        if(type == "unrestricted float")
            return "float";
        if(type == "double")
            return "double";
        if(type == "unrestricted double")
            return "double";
        if(type == "DOMString")
            return "DOMString";
        if(type == "USVString")
            return "USVString";
        if(type == "ByteString")
            return "ByteString";

        if(type[type.size() - 1] == pointerSign)
        {
            type[type.size() - 1] = pointerSignCpp;
            return type;
        }
        else return type + referenceSuffix;
    }

    std::string Function::convertArguments(const std::string original, const IDL* idl)
    {
        std::string str = original;

        return str;
    }

}
