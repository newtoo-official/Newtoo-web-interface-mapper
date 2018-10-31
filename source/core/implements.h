#pragma once

#include "definition.h"

namespace NewtooWebInterfaceMapper_core
{
    class Implements : public Definition
    {
    public:
        Implements(IDL* aIdl, std::string decl, bool aIncludes);

        void cascade() override;

        std::string& interface();
        std::string& implements();

        bool includes();

    private:
        std::string originalDeclaration();

        std::string mInterface;
        std::string mImplements;
        IDL* mIdl;
        bool mIncludes;
    };
}
