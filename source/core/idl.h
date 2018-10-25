#pragma once

#include <string>
#include <vector>

namespace NewtooWebInterfaceMapper_core
{
    class Definition;
    class DefinitionList;

    typedef std::vector<std::string> DeclarationStringList;
    typedef std::vector<std::string> Log;

    class IDL
    {
    public:
        IDL(std::string text);

        void serialize();
        void clear();

        std::string& header();
        std::string& source();
        Log& log();

        DefinitionList& definitions();

    private:
        static DeclarationStringList declarationListFrom(std::string str);
    };
}
