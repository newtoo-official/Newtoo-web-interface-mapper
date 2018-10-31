#pragma once

#include <string>
#include <vector>

namespace NewtooWebInterfaceMapper_core
{
    class IDL;

    class Function
    {
    public:

        static std::string toC_StyleType(std::string type, IDL* idl);


        struct Type
        {
            std::string text;
            bool isStringType;
            Type(std::string aText, IDL* idl, bool turnToList = false, bool aIsStringType = false);
        };
        static Type typeFromString(std::string type, IDL* idl);

        static std::string convertArguments(const std::string original, IDL* idl);
        /*
            void merge(optional Node* child);
                      ^  -- arguments --  ^
        */

        static void splitSequentialListString(std::vector<std::string>& list, std::string* target);
    };
}
