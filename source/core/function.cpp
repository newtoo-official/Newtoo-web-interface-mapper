#include "function.h"
#include "interface.h"
#include "dictionary.h"
#include "argument.h"
#include "idl.h"

namespace NewtooWebInterfaceMapper_core
{

    const char pointerSignCpp = '*';
    const char pointerSign = '?';

    const char referenceSuffix = '&';

    std::string convertSequence(std::string& type, IDL* idl)
    {
        std::size_t start = type.find('<');
        type = idl->settings().getSequence() + '<'
                + Function::toC_StyleType(type.substr(start + 1, type.size() - start - 2), idl) + ">&";
        return type;
    }

    bool turnTypeToList(std::string& type)
    {
        std::size_t sequenceSuffix = type.find("...");
        bool ret = sequenceSuffix != std::string::npos;
        if(ret)
        {
            type.erase(sequenceSuffix, 3);
        }
        return ret;
    }

    void postprocessType(std::string& type, bool turnToList, IDL* idl)
    {
        if(turnToList)
        {
            type = idl->settings().getSequence() + '<' + type + '>';
        }
    }

    Function::Type::Type(std::string aText, IDL* idl, bool turnToList,  bool aIsStringType)
        :text(aText), isStringType(aIsStringType)
    {
        postprocessType(text, turnToList, idl);
    }

    Function::Type Function::typeFromString(std::string type, IDL* idl)
    {
        bool toList = turnTypeToList(type);

        if(type == "byte")
            return Type("signed char", idl, toList);
        else if(type == "ocetet")
            return Type("unsigned char", idl, toList);
        else if(type == "short")
            return Type("short", idl, toList);
        else if(type == "unsigned short")
            return Type("unsigned short", idl, toList);
        else if(type == "long")
            return Type("long", idl, toList);
        else if(type == "unsigned long")
            return Type("unsigned long", idl, toList);
        else if(type == "float")
            return Type("float", idl, toList);
        else if(type == "unrestricted float")
            return Type("float", idl, toList);
        else if(type == "double")
            return Type("double", idl, toList);
        else if(type == "unrestricted double")
            return Type("double", idl, toList);
        else if(type == "DOMString")
        {
            return Type("DOMString", idl, toList, true);
        }
        else if(type == "CSSOMString")
        {
            return Type("CSSOMString", idl, toList, true);
        }
        else if(type == "USVString")
        {
            return Type("USVString", idl, toList, true);
        }
        else if(type == "ByteString")
        {
            return Type("ByteString", idl, toList, true);
        }
        else if(type == "boolean")
            return Type("bool", idl, toList);
        else if(type == "void")
            return Type("void", idl, toList);
        else if(type == "any")
            return Type("double", idl, toList);
        else if(type.find("sequence<") == 0)
            return Type(convertSequence(type, idl), idl, toList);

        else if(idl->definitions().findEnumeration(type) != 0)
            return Type(type, idl, toList);

        else if(type[type.size() - 1] == pointerSign)
        {
            type[type.size() - 1] = pointerSignCpp;
            return Type(type, idl, toList);
        }
        else return Type(type + referenceSuffix, idl, toList);
    }

    std::string convertType(std::string type, IDL* idl)
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

        else if(idl->definitions().findEnumeration(type) != 0)
            return type;

        else if(type[type.size() - 1] == pointerSign)
        {
            type[type.size() - 1] = pointerSignCpp;
            return type;
        }
#ifdef typedef_convert_type
        else return type;
#else
        else return type + referenceSuffix;
#endif
    }

    std::string Function::toC_StyleType(std::string type, IDL* idl)
    {
        bool toList = turnTypeToList(type);
        std::string ret = convertType(type, idl);
        postprocessType(ret, toList, idl);
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
