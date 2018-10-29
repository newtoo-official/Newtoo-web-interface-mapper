#include "function.h"
#include "interface.h"
#include "idl.h"

namespace NewtooWebInterfaceMapper_core
{

    const char pointerSignCpp = '*';
    const char pointerSign = '?';

    const char referenceSuffix = '&';

    std::string Function::toC_StyleType(std::string type)
    {
        if(type == "byte")
            return "signed char";
        else if(type == "ocetet")
            return "unsigned char";
        else if(type == "short")
            return "short";
        else if(type == "unsigned short")
            return "unsigned short";
        else if(type == "long")
            return "long";
        else if(type == "unsigned long")
            return "unsigned long";
        else if(type == "float")
            return "float";
        else if(type == "unrestricted float")
            return "float";
        else if(type == "double")
            return "double";
        else if(type == "unrestricted double")
            return "double";
        else if(type == "DOMString")
            return "DOMString";
        else if(type == "USVString")
            return "USVString";
        else if(type == "ByteString")
            return "ByteString";
        else if(type == "boolean")
            return "bool";
        else if(type == "void")
            return "void";
        else if(type.find("sequence<") == 0)
        {
            std::size_t start = type.find('<');
            type = "sequence<" + toC_StyleType(type.substr(start + 1, type.size() - start - 2)) + '>';
            return type;
        }

        else if(type[type.size() - 1] == pointerSign)
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
