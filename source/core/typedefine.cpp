#include "typedefine.h"
#include "function.h"
#include "idl.h"

namespace NewtooWebInterfaceMapper_core
{
    TypeDefine::TypeDefine(IDL* aIdl, std::string decl)
        :Definition(TYPEDEFINE, aIdl), mIdl(aIdl)
    {
        // Вырезать дополнительные параметры
        std::size_t extAttrEnd = decl.find(']');
        if(extAttrEnd != std::string::npos)
            decl.erase(0, extAttrEnd + 1);
        while(decl[0] == ' ')
            decl.erase(0, 1);

        if(decl.find("typedef ") == 0)
            decl.erase(0, 8);

        std::size_t splitter = decl.find(' ');

        if(splitter == std::string::npos)
        {
            aIdl->error(aIdl->invalidSyntaxError(decl));
            return;
        }

        mOriginalType = convertType(decl.substr(0, splitter));
        mNewType = decl.substr(splitter + 1, decl.size() - splitter - 2);
    }

    std::string TypeDefine::serializeHeader()
    {
        return "typedef " + mOriginalType + ' ' + mNewType + ";\n\n";
    }

    std::string& TypeDefine::originalType()
    {
        return mOriginalType;
    }
    std::string& TypeDefine::newType()
    {
        return mNewType;
    }

    std::string TypeDefine::convertType(std::string type)
    {
#define typedef_convert_type
        return Function::toC_StyleType(type, mIdl);
#undef typedef_convert_type
    }
}
