#pragma once

#include <string>

namespace NewtooWebInterfaceMapper_core
{
    class IDL;

    class Function
    {
    public:

        static std::string toC_StyleType(std::string& type);

        static std::string convertDictonaryInner(const std::string original, const IDL* idl);
        /*
            dictionary BurgerOrder
            {

              unsigned long pattyCount;         <= dictonary inner
              unsigned long cheeseSliceCount;

            };
        */

        static std::string convertArguments(const std::string original, const IDL* idl);
        /*
            void merge(optional Node* child);
                      ^  -- arguments --  ^
        */
    };
}
