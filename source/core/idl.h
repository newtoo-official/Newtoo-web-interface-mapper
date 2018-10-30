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

    const char WarningPrefix[] = "Warning: ";
    const char ErrorPrefix[] = "Error: ";

    class IDL
    {
    public:
        IDL(std::string text, NewtooWebInterfaceMapper::Settings& settings);

        NewtooWebInterfaceMapper::Settings& settings();

        std::string invalidSyntaxError(std::string fragment);
        std::string atLineSuffix(std::string fragment);

        std::string& header();
        std::string& source();
        std::string& aboveSource();
        Log& log();

        void alert(std::string message);
        void error(std::string message);
        void warning(std::string message);

        DefinitionList& definitions();

        unsigned long getLine(std::string fragment);
        const unsigned long FragmentNotFound = 0;

    private:

        void serialize();

        NewtooWebInterfaceMapper::Settings& mSettings;

        unsigned short mWarningCounter;
        unsigned short mErrorCounter;

        std::string mHeader;
        std::string mSource;
        std::string mAboveSource;
        Log mLog;

        DefinitionList mDefinitions;

        std::string mOriginalText;

        static DeclarationStringList declarationListFrom(std::string str);
    };
}
