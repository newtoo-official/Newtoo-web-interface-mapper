#include "function.h"
#include "interface.h"
#include "dictionary.h"
#include "argument.h"
#include "idl.h"
#include "iostream"

namespace NewtooWebInterfaceMapper_core
{

    const char pointerSignCpp = '*';
    const char pointerSign = '?';

    const char referenceSuffix = '&';

    std::string convertSequence(std::string& type, IDL* idl)
    {
        std::size_t start = type.find('<');
        type = idl->settings().getSequence() + '<' + Function::toC_StylePlainType(type.substr(start + 1,
                                                type.size() - start - 2), idl) + ">&";
        return type;
    }

    const char PromiseTemplateStart[] = "Promise<";

    std::string convertPromise(std::string& type, IDL* idl)
    {
        std::size_t start = type.find('<');
        type = PromiseTemplateStart + Function::toC_StylePlainType(type.substr(start + 1, type.size()
                                                                - start - 2), idl) + ">&";
        return type;
    }

    bool turnTypeToArray(std::string& type)
    {
        std::size_t extensionSuffix = type.find("...");
        bool ret = extensionSuffix != std::string::npos;
        if(ret)
        {
            type.erase(extensionSuffix, 3);
        }
        std::size_t arraySuffix = type.find("[]");
        if(arraySuffix != std::string::npos)
        {
            type.erase(arraySuffix, 2);
            ret = true;
        }
        return ret;
    }

    void postprocessType(std::string& type, bool turnToArray, IDL* idl)
    {
        if(turnToArray)
        {
            type = idl->settings().getArray() + '<' + type + '>';
        }
    }

    void preprocessType(std::string& type)
    {
        std::size_t openBracket = type.find('(');
        std::size_t closeBracket = type.find(')');

        if(openBracket != std::string::npos and closeBracket != std::string::npos)
        {
            type = type.erase(closeBracket, 1);
            type = type.erase(openBracket, 1);

            while(type.find(" or ") != std::string::npos)
                type = type.replace(type.find(" or "), 4, "Or");

            while(type.find(' ') != std::string::npos)
                type.erase(type.find(' '), 1);
        }
    }

    Function::Type::Type(std::string aText, IDL* idl, bool turnToList,  bool aIsStringType)
        :text(aText), isStringType(aIsStringType)
    {
        postprocessType(text, turnToList, idl);
    }

    Function::Type Function::typeFromString(std::string type, IDL* idl)
    {
        preprocessType(type);

        bool toArray = turnTypeToArray(type);

        if(type == "byte")
            return Type("signed char", idl, toArray);
        else if(type == "ocetet")
            return Type("unsigned char", idl, toArray);
        else if(type == "short")
            return Type("short", idl, toArray);
        else if(type == "unsigned short")
            return Type("unsigned short", idl, toArray);
        else if(type == "long")
            return Type("long", idl, toArray);
        else if(type == "unsigned long")
            return Type("unsigned long", idl, toArray);
        else if(type == "float")
            return Type("float", idl, toArray);
        else if(type == "unrestricted float")
            return Type("float", idl, toArray);
        else if(type == "double")
            return Type("double", idl, toArray);
        else if(type == "unrestricted double")
            return Type("double", idl, toArray);
        else if(type == "DOMString")
        {
            return Type("DOMString", idl, toArray, true);
        }
        else if(type == "CSSOMString")
        {
            return Type("CSSOMString", idl, toArray, true);
        }
        else if(type == "USVString")
        {
            return Type("USVString", idl, toArray, true);
        }
        else if(type == "ByteString")
        {
            return Type("ByteString", idl, toArray, true);
        }
        else if(type == "boolean")
            return Type("bool", idl, toArray);
        else if(type == "void")
            return Type("void", idl, toArray);
        else if(type == "any")
            return Type("double", idl, toArray);
        else if(type.find("sequence<") == 0)
            return Type(convertSequence(type, idl), idl, toArray);
        else if(type.find("Promise<") == 0)
            return Type(convertPromise(type, idl), idl, toArray);

        else if(idl->definitions().findEnumeration(type) != 0)
            return Type(type, idl, toArray);

        else if(type[type.size() - 1] == pointerSign)
        {
            type[type.size() - 1] = pointerSignCpp;

            if(type == "DOMString*" or type == "CSSOMString*" or type == "USVString*")
                return Type(idl->settings().getStringPointerClass(), idl, toArray);

            return Type(type, idl, toArray);
        }
        else return Type(type + referenceSuffix, idl, toArray);
    }

    std::string convertType(std::string type, IDL* idl)
    {
        preprocessType(type);

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
        else if(type == "CSSOMString")
            return "CSSOMString";
        else if(type == "USVString")
            return "USVString";
        else if(type == "ByteString")
            return "ByteString";
        else if(type == "boolean")
            return "bool";
        else if(type == "void")
            return "void";
        else if(type == "any")
            return "double";
        else if(type.find("sequence<") == 0)
            return convertSequence(type, idl);
        else if(type.find("Promise<") == 0)
            return convertPromise(type, idl);

        else if(idl->definitions().findEnumeration(type) != 0)
            return type;

        else if(type[type.size() - 1] == pointerSign)
        {
            type[type.size() - 1] = pointerSignCpp;

            if(type == "DOMString*" or type == "CSSOMString*" or type == "USVString*")
                return idl->settings().getStringPointerClass();

            return type;
        }
        else return type + referenceSuffix;
    }

    std::string Function::toC_StyleType(std::string type, IDL* idl)
    {
        bool toArray = turnTypeToArray(type);
        std::string ret = convertType(type, idl);
        postprocessType(ret, toArray, idl);
        return ret;
    }

    std::string Function::toC_StylePlainType(std::string type, IDL* idl)
    {
        std::string ret = toC_StyleType(type, idl);
        if(ret[ret.size() - 1] == referenceSuffix)
            ret.erase(ret.size() - 1, 1);
        return ret;
    }

    std::string Function::convertArguments(const std::string original, IDL* idl)
    {
        if(original.empty())
            return nullstr;

        std::vector<std::string> list;
        list.push_back(original);
        splitSequentialListString(list, &list.back());
        std::string str;

        std::size_t lastDeclIndex = list.size() - 1;

        for(unsigned i = 0; i < list.size(); i++)
        {
            std::string argdecl = list[i];

            if(argdecl[0] == ' ')
                argdecl.erase(0, 1);

            // Убрать устарелые префиксы
            if(argdecl.find("in ") != std::string::npos)
                argdecl.erase(0, 3);

            bool isOptional = false;
            if(argdecl.find("optional ") != std::string::npos)
            {
                isOptional = true;
                argdecl.erase(0, 9);
            }

            Argument arg(argdecl, idl, isOptional);

            if(arg.isValid())
            {
                str += arg.toString();
            } else
            {
                idl->error(idl->invalidSyntaxError(original));
            }

            if(i != lastDeclIndex)
                str += ", ";
        }
        return str;
    }

    const char closeArgBracket = ')';
    const char openArgBracket = '(';
    const char splitter = ',';

    void Function::splitSequentialListString(std::vector<std::string>& list, std::string* target)
    {
        std::size_t splitterIndex;
        bool inBrackets = false;

        bool found = false;
        for(unsigned i = 0; i < target->size(); i++)
        {
            char c = target->at(i);
            if(!inBrackets)
            {
                if(c == openArgBracket)
                {
                    inBrackets = true;
                }
                else if(c == splitter)
                {
                    splitterIndex = i;
                    found = true;
                    break;
                }
            } else
            {
                if(c == closeArgBracket)
                    inBrackets = false;
            }
        }

        if(!found)
            return;

        std::string next = target->substr(splitterIndex + 1, target->size() - splitterIndex - 1);
        *target = target->substr(0, splitterIndex);
        list.push_back(next);
        splitSequentialListString(list, &list.back());
    }

}
