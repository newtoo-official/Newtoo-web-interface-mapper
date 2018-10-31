#pragma once

#include "definition.h"

namespace NewtooWebInterfaceMapper_core
{
    class TypeDefine : public Definition
    {
    public:
        TypeDefine(IDL* aIdl, std::string decl);

        std::string serializeHeader() override;

        std::string& originalType();
        std::string& newType();

    private:
        std::string convertType(std::string type);

        std::string mOriginalType;
        std::string mNewType;
        IDL* mIdl;
    };
}
