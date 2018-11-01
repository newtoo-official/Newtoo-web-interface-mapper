#include "implements.h"
#include "interface.h"
#include "idl.h"

namespace NewtooWebInterfaceMapper_core
{

    Implements::Implements(IDL* aIdl, std::string decl, bool aIncludes)
        :Definition(IMPLEMENTS, aIdl), mIdl(aIdl), mIncludes(aIncludes)
    {
        // Вырезать дополнительные параметры
        std::size_t extAttrEnd = decl.find(']');
        if(extAttrEnd != std::string::npos)
            decl.erase(0, extAttrEnd + 1);
        while(decl[0] == ' ')
            decl.erase(0, 1);

        std::size_t interfaceNameEnd = decl.find(' ');
        std::size_t implementsNameStart = decl.find_last_of(' ');

        if(interfaceNameEnd == std::string::npos or implementsNameStart == std::string::npos)
        {
            aIdl->error(aIdl->invalidSyntaxError(decl));
            return;
        }
        implementsNameStart++;

        mInterface = decl.substr(0, interfaceNameEnd);
        mImplements = decl.substr(implementsNameStart, decl.size() - implementsNameStart - 1);
    }

    void Implements::cascade()
    {
        if(interface() == implements())
        {
            mIdl->error("Interface \"" + interface() + "\" implements itself"
                           + mIdl->atLineSuffix(originalDeclaration()));
            return;
        }

        Interface* interfaceTarget = mIdl->definitions().findInterface(interface());
        if(interfaceTarget == 0)
        {
            mIdl->error("Interface \"" + interface() + "\" not declared"
                           + mIdl->atLineSuffix(originalDeclaration()));
            return;
        } else
        {
            if(interfaceTarget->isCallback())
            {
                mIdl->error("Callback interface \"" + interface()
                            + "\" cannot implement any other interface."
                               + mIdl->atLineSuffix(originalDeclaration()));
            }
        }

        Interface* implementsTarget = mIdl->definitions().findInterface(implements());
        if(implementsTarget == 0)
        {
            mIdl->warning("Interface \"" + interface() + "\" implements not declared interface \""
                           + implements() + "\"" + mIdl->atLineSuffix(originalDeclaration()));
        } else
        {
            if(implementsTarget->isCallback())
            {
                mIdl->error("Callback interface \"" + interface() + "\" cannot be implemented."
                               + mIdl->atLineSuffix(originalDeclaration()));
            }
        }

        if(interfaceTarget->headerInherit().empty())
            interfaceTarget->headerInherit() = " : public " + implements();
        else
            interfaceTarget->headerInherit() += ", public " + implements();
    }

    std::string& Implements::interface()
    {
        return mInterface;
    }
    std::string& Implements::implements()
    {
        return mImplements;
    }

    bool Implements::includes()
    {
        return mIncludes;
    }

    std::string Implements::originalDeclaration()
    {
        if(!includes())
            return interface() + " implements " + implements();
        else
            return interface() + " includes " + implements();
    }
}
