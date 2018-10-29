#pragma once

#include "extattrmap.h"

#include <string>
#include <vector>

namespace NewtooWebInterfaceMapper_core
{
    class Interface;
    class IDL;

    enum InterfaceUnitType
    {
        ATTRIBUTE_TYPE,
        CONSTANT_TYPE,
        FUNCTION_TYPE,
        BAD_UNIT_TYPE
    };

    class InterfaceUnit
    {
    public:
        InterfaceUnit(std::string decl, IDL* idl);
        ~InterfaceUnit();

        ExtAttrMap& extattrs();

        std::string& type();
        std::string& identifer();
        std::string& args();

        bool isReadonlyOrStatic() const;

        InterfaceUnitType unitType() const;

    private:
        ExtAttrMap* mExtattrs;

        std::string mType;
        std::string mIdentifer;
        std::string mArgs;

        bool mIsReadonlyOrStatic;

        InterfaceUnitType mUnitType;
    };

    typedef std::vector<InterfaceUnit> InterfaceUnitList;

    class InterfaceInner
    {
    public:
        static void parseInner(std::string str, Interface* assignedInterface);

    };
}
