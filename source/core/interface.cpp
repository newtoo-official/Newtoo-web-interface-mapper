#include "interface.h"
#include "idl.h"
#include "iostream"

namespace NewtooWebInterfaceMapper_core
{
    Interface::Interface(IDL* aIdl, std::string decl)
        :Definition(INTERFACE, aIdl), mIsPartial(false)
    {

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
        return mCopyConstructorStart + mCopyConstructorInitFields + mCopyConstructorInitFieldsAppendix
                + mCopyConstructorEnd + mSource;
    }
    std::string Interface::serializeSource_Interface()
    {
        return mHeaderStart + mHeaderInherit + headerPublicPrefix() + mHeaderPublic
                + mHeaderPublicAppendix + mHeaderPrivate + mHeaderPrivateAppendix + mHeaderEnd;
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

    const char classMemberPrefix = 'm';

    std::string toClassMemberStyle(const std::string name)
    {
        std::string str = std::to_string(classMemberPrefix);
        str += name;
        str[1] = toupper(str[1]);
        return str;
    }

    const char namespaceSuffix[] = "::";

    const char openBracket[] = "\n{\n\n";
    const char closeBracket[] = "}\n";

    const char referenceSuffix = '&';

    std::size_t typeEndIndex(std::string& attributeAfter) // ex. unsigned long width;
    {
        return attributeAfter.find_last_of(whitespace);
    }

    std::string toC_StyleType(std::string& type)
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

        return type + referenceSuffix;
    }

    void Interface::addAttribute(bool isReadOnly, ExtAttrMap& extattrs, std::string& type,
                                 std::string& identifer)
    {
        if(isReadOnly)
        {
            if(extattrs.sameObject() != 0)
            {

            } else
            {
                mHeaderPublic += type + whitespace;
                mHeaderPublic += identifer + "();";

                mSource += type + whitespace;
                mSource += interfaceName() + namespaceSuffix;
                mSource += identifer + "()\n{\n\n}\n";
            }
        }
        else
        {
            if(extattrs.sameObject() != 0)
            {

            } else
            {

            }
        }
    }

    std::string Interface::headerPublicPrefix()
    {
        return "{\n    public:\n";
    }

    bool Interface::isPartial() const
    {
        return mIsPartial;
    }
}
