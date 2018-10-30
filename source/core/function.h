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
            Type(std::string aText, bool aIsStringType = false);
        };
        static Type typeFromString(std::string type, IDL* idl);


        static std::string convertDictonaryInner(const std::string original, IDL* idl);
        /*
            dictionary BurgerOrder
            {

              unsigned long pattyCount;         <= dictonary inner
              unsigned long cheeseSliceCount;

            };
        */

        static std::string convertArguments(const std::string original, IDL* idl);
        /*
            void merge(optional Node* child);
                      ^  -- arguments --  ^
        */

        static void splitSequentialListString(std::vector<std::string>& list, std::string* target);
    };
}
