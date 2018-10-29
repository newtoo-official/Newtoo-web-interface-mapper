#include "interface.h"
#include "idl.h"
#include "function.h"

#define copyConstructorStartDict interfaceName() + "::" + interfaceName() + '(' \
    + interfaceName() + "& ref)"

#define headerPublicPrefixCopyConstructorDict "    " + interfaceName() + '(' + interfaceName() \
    + "& ref);\n"

namespace NewtooWebInterfaceMapper_core
{

    const char tab[] = "    ";
    const char doubleSpace[] = "  ";

    std::string constructorArguments(const std::string original, IDL* idl)
    {
        std::string str = original;
        std::size_t argsIndex = str.find('(');
        if(argsIndex != std::string::npos)
        {
            argsIndex++;
            str = str.substr(argsIndex, str.size() - argsIndex - 2);
            str = Function::convertArguments(str, idl);
            return str;
        }
        return "";
    }

    Interface::Interface(IDL* aIdl, std::string decl)
        :Definition(INTERFACE, aIdl), mIsPartial(false)
    {
        // Назначить дополнительные параметры
        std::string after = decl.substr(0, decl.find('{'));
        std::size_t extAttrEnd = after.find(']');
        std::string extAttrString;
        if(extAttrEnd != std::string::npos)
        {
            extAttrString = after.substr(1, extAttrEnd - 1);
            decl.erase(0, extAttrEnd + 1);
        }

        // Удалить пробелы, чтобы правильно назначить название интерфейса
        while(decl.find(' ') == 0)
            decl.erase(0, 1);

        // Назначить название интерфейса
        std::size_t nameIndex = decl.find(' ');
        nameIndex++;
        std::size_t inheritsIndex = decl.find(':');
        std::size_t openBracketIndex = decl.find('{');
        if(inheritsIndex == std::string::npos)
            mInterfaceName = decl.substr(nameIndex, openBracketIndex - nameIndex);
        else
        {
            mInterfaceName = decl.substr(nameIndex, inheritsIndex - nameIndex);
        }
        if(mInterfaceName[mInterfaceName.size() - 1] == ' ')
            mInterfaceName.erase(mInterfaceName.size() - 1);

        mHeaderStart = "class " + mInterfaceName;

        // Добавить окончание
        mHeaderEnd = "\n};\n\n";

        // Создать карту дополнительных параметров
        ExtAttrMap extAttrMap(extAttrString);

        // Добавить конструкторы
        if(extAttrMap.constructor() != 0)
        {
            for(unsigned i = 0; i < extAttrMap.list().size(); i++)
            {
                if(extAttrMap.list()[i].type() != CONSTRUCTOR_TYPE)
                    continue;

                std::string args = constructorArguments(extAttrMap.list()[i].name(), aIdl);
                mSource += mInterfaceName + "::" + mInterfaceName + "("+args+")\n{\n\n}\n\n";
                mHeaderPublic += tab + mInterfaceName + "(" + args + ");\n";
            }
        }
        if(extAttrMap.namedContructor() != 0)
        {
            for(unsigned i = 0; i < extAttrMap.list().size(); i++)
            {
                if(extAttrMap.list()[i].type() != NAMED_CONSTRUCTOR_TYPE)
                    continue;

                std::string value = extAttrMap.list()[i].value();

                std::size_t argsIndex = value.find('(');
                if(argsIndex == std::string::npos)
                    continue;
                argsIndex++;

                std::string args = value.substr(argsIndex, value.size() - argsIndex - 2);
                args = Function::convertArguments(args, aIdl);
\
                mSource += mInterfaceName + "::" + mInterfaceName + "("+args+")\n{\n\n}\n\n";
                mHeaderPublic += tab + mInterfaceName + "(" + args + ");\n";

                std::string constructorName = value.substr(0, argsIndex - 1);

                mHeaderEnd += "typedef " + mInterfaceName + " "+ constructorName +";\n\n";
            }
        }

        // Добавить конструктор копирования
        mHeaderPublicPrefix = "{\npublic:\n";
        mHeaderPublicPrefix += headerPublicPrefixCopyConstructorDict;

        // Добавить конструктор по-умолчанию
        mHeaderPublic += tab + mInterfaceName + "();\n\n";
        mSource += mInterfaceName + "::" + mInterfaceName + "()\n{\n\n}\n\n";

        // Назначить наследование
        if(inheritsIndex != std::string::npos)
        {
            std::string inherits = decl.substr(inheritsIndex + 1, openBracketIndex - inheritsIndex - 1);

            while(inherits.find(' ') != std::string::npos)
                inherits = inherits.replace(inherits.find(' '), 1, "");

            mHeaderInherit = " : public " + inherits + '\n';

            mCopyConstructorInitFields = " : " + inherits + "(ref)";
        }

        // Добавить реализацию конструктора копирования
        mCopyConstructorStart = copyConstructorStartDict;
        mCopyConstructorEnd = "\n{}\n\n";

        // Добавить приватные поля
        mHeaderPrivate = "\n\nprivate:\n";

        std::size_t closeBracketIndex = decl.find('}');
        if(closeBracketIndex == std::string::npos)
            return;

        //Добавить содержимое

        std::string inner = decl.substr(openBracketIndex + 1, closeBracketIndex - openBracketIndex - 1);

        while(inner.find(doubleSpace) != std::string::npos)
            inner = inner.replace(inner.find(doubleSpace), 2, "");

        InterfaceInner::parseInner(inner, this);
    }

    std::string& Interface::interfaceName()
    {
        return mInterfaceName;
    }

    std::string& Interface::copyConstructorStart()
    {
        return mCopyConstructorStart;
    }
    std::string& Interface::copyConstructorInitFields()
    {
        return mCopyConstructorInitFields;
    }
    std::string& Interface::copyConstructorInitFieldsAppendix()
    {
        return mCopyConstructorInitFieldsAppendix;
    }
    std::string& Interface::copyConstructorEnd()
    {
        return mCopyConstructorEnd;
    }
    std::string& Interface::headerStart()
    {
        return mHeaderStart;
    }
    std::string& Interface::headerInherit()
    {
        return mHeaderInherit;
    }
    std::string& Interface::headerPublic()
    {
        return mHeaderPublic;
    }
    std::string& Interface::headerPublicPrefix()
    {
        return mHeaderPublicPrefix;
    }
    std::string& Interface::headerPublicAppendix()
    {
        return mHeaderPublicAppendix;
    }
    std::string& Interface::headerPrivate()
    {
        return mHeaderPrivate;
    }
    std::string& Interface::headerPrivateAppendix()
    {
        return mHeaderPrivateAppendix;
    }
    std::string& Interface::headerEnd()
    {
        return mHeaderEnd;
    }
    std::string& Interface::source()
    {
        return mSource;
    }

    std::string Interface::serializeHeader_Interface()
    {
        return mHeaderStart + mHeaderInherit + headerPublicPrefix() + mHeaderPublic
                + mHeaderPublicAppendix + mHeaderPrivate + mHeaderPrivateAppendix + mHeaderEnd;
    }

    void adoptPartiallyAddedInitFields(std::string& initFields, std::string& initFieldsAppendix)
    {
        if(initFieldsAppendix.find(" : ") == 0)
            initFieldsAppendix.erase(0, 4);
        while(initFieldsAppendix.find(" : ") != std::string::npos)
            initFieldsAppendix.replace(initFieldsAppendix.find(" : "),
                                                       1, "");
        if(!initFieldsAppendix.empty() and initFields.empty())
            initFields += " : ";
    }

    std::string Interface::serializeSource_Interface()
    {
        adoptPartiallyAddedInitFields(mCopyConstructorInitFields, mCopyConstructorInitFieldsAppendix);

        return mCopyConstructorStart + mCopyConstructorInitFields + mCopyConstructorInitFieldsAppendix
                + mCopyConstructorEnd + mSource;
    }

    std::string Interface::serializeHeader()
    {
        return serializeHeader_Interface();
    }
    std::string Interface::serializeSource()
    {
        return serializeSource_Interface();
    }

    void Interface::cascade()
    {
        if(!isPartial())
            return;

        Interface* reference = idl()->definitions().findInterface(interfaceName());
        if(reference != 0)
        {
            reference->append(headerPublic(), headerPrivate(), copyConstructorInitFields(), source());
        }
    }

    const char whitespace = ' ';
    const char newline = '\n';
    const char initFieldsPrefix = ':';
    const char initFieldsSplitter = ',';

    void Interface::append(std::string partialHeaderPublic, std::string partialHeaderPrivate,
                           std::string partialCopyConstructorInitFields, std::string partialSource)
    {
        if(partialCopyConstructorInitFields[0] == initFieldsPrefix)
            partialCopyConstructorInitFields.erase(0, 1);
        if(partialCopyConstructorInitFields[0] == whitespace)
            partialCopyConstructorInitFields.erase(0, 1);
        partialCopyConstructorInitFields = initFieldsSplitter + partialCopyConstructorInitFields;

        headerPublicAppendix() += newline;
        headerPublicAppendix() += partialHeaderPublic;
        headerPrivateAppendix() += newline;
        headerPrivateAppendix() += partialHeaderPrivate;
        copyConstructorInitFieldsAppendix() += partialCopyConstructorInitFields;
        source() += partialSource;
    }

    std::string setAttrStr(std::string get)
    {
        get[0] = toupper(get[0]);
        get = "set" + get;
        return get;
    }

    std::string argAttrStr(std::string get)
    {
        get[0] = toupper(get[0]);
        get = "a" + get;
        return get;
    }

    const char classMemberPrefix[] = "m";

    std::string toClassMemberStyle(const std::string name)
    {
        std::string str = classMemberPrefix;
        str += name;
        str[1] = toupper(str[1]);
        return str;
    }

    void Interface::appendMemberToCopyConstructor(std::string member)
    {
        if(mCopyConstructorInitFields.empty())
        {
            mCopyConstructorInitFields += " : " + member + "(ref)";
        } else
        {
            mCopyConstructorInitFields += ", " + member + "(ref)";
        }
    }

    void Interface::appendUnit(InterfaceUnit unit)
    {
        switch(unit.unitType())
        {
            case ATTRIBUTE_TYPE:
            {
                std::size_t referenceIndex = unit.type().find('&');
                if(unit.extattrs().newObject() != 0 and referenceIndex != std::string::npos)
                    unit.type() = unit.type().replace(referenceIndex, 1, "");

                if(unit.extattrs().sameObject() == 0)
                {
                    mHeaderPublic += tab + unit.type() + ' ' + unit.identifer() + "();\n";
                    mSource += unit.type() + ' ' + interfaceName() + "::" + unit.identifer()
                            + "()\n{\n\n}\n\n";

                    if(!unit.isReadonlyOrStatic())
                    {
                        mHeaderPublic += tab;
                        mHeaderPublic += "void " + setAttrStr(unit.identifer()) + "("
                                + unit.type() + ' ' + argAttrStr(unit.identifer()) + ");\n";
                        mSource += "void " + interfaceName() + "::" + setAttrStr(unit.identifer())
                                + "(" + unit.type() + ' ' + argAttrStr(unit.identifer())
                                + ")\n{\n\n}\n\n";
                    }
                } else
                {
                    std::string member = toClassMemberStyle(unit.identifer());
                    std::string objType = unit.type();
                    std::size_t typeRefIndex = objType.find('&');
                    if(typeRefIndex != std::string::npos)
                        objType = objType.replace(typeRefIndex, 1, "");

                    mHeaderPublic += tab + unit.type() + ' ' + unit.identifer() + "() const;\n";
                    mSource += unit.type() + ' ' + interfaceName() + "::" + unit.identifer()
                            + "() const\n{\n    return " + member + ";\n}\n\n";
                    mHeaderPrivate += tab + objType + ' ' + member + ";\n";

                    appendMemberToCopyConstructor(member);

                    if(!unit.isReadonlyOrStatic())
                    {
                        mHeaderPublic += tab;
                        mHeaderPublic += "void " + setAttrStr(unit.identifer()) + "("
                                + unit.type() + ' ' + argAttrStr(unit.identifer()) + ");\n";
                        mSource += "void " + interfaceName() + "::" + setAttrStr(unit.identifer())
                                + "(" + unit.type() + ' ' + argAttrStr(unit.identifer())
                                + ")\n{\n" + member + " = " + argAttrStr(unit.identifer()) + ";\n}\n\n";
                    }
                }
                mHeaderPublic += '\n';
                break;
            }
            case FUNCTION_TYPE:
            {
                mHeaderPublic += tab;

                std::string prefix;
                if(unit.isReadonlyOrStatic())
                    prefix = "static ";

                mHeaderPublic += prefix + unit.type() + ' ' + unit.identifer() + '(' + unit.args()
                        + ");\n\n";

                mSource += unit.type() + ' ' + interfaceName() + "::" + unit.identifer() + '('
                        + unit.args() + ")\n{\n\n}\n\n";
                break;
            }
            case CONSTANT_TYPE:
            {
                mHeaderPublic += tab;
                mHeaderPublic += "const " + unit.type() + ' ' + unit.identifer() + " = " + unit.args()
                        + ";\n\n";
                break;
            }
            case BAD_UNIT_TYPE:
            {
                break;
            }
        }
    }

    std::string Interface::includeDirective()
    {
        return "#include \"" + mInterfaceName + ".h\"\n";
    }

    void Interface::modifySource(std::string& source)
    {
        if(source[0] != '#')
        {
            source = includeDirective() + '\n' + source;
        } else
        {
            source = includeDirective() + source;
        }
    }

    const char namespaceSuffix[] = "::";

    const char openBracket[] = "\n{\n\n";
    const char closeBracket[] = "}\n";

    const char referenceSuffix = '&';

    std::size_t typeEndIndex(std::string& attributeAfter) // ex. unsigned long width;
    {
        return attributeAfter.find_last_of(whitespace);
    }

    bool Interface::isPartial() const
    {
        return mIsPartial;
    }
}
