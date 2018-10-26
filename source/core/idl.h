#pragma once

#include "../shared/settings.h"
#include "definitionlist.h"

#include <string>
#include <vector>

namespace NewtooWebInterfaceMapper_core
{
    class Definition;

    typedef std::vector<std::string> DeclarationStringList;
    typedef std::vector<std::string> Log;

    class IDL
    {
    public:
        IDL(std::string text, NewtooWebInterfaceMapper::Settings& settings);

        std::string& header();
        std::string& source();
        Log& log();

    private:

        DefinitionList& definitions();

        void serialize();

        NewtooWebInterfaceMapper::Settings& mSettings;

        std::string mHeader;
        std::string mSource;
        Log mLog;

        DefinitionList mDefinitions;

        static DeclarationStringList declarationListFrom(std::string str);
    };
}