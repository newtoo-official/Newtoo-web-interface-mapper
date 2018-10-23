#pragma once

#include "string"

#include "../shared/settings.h"

namespace webidl2cpp_core
{
    class InterfaceList;
    class Interface;
    class DictonaryList;
    class Dictonary;
    class Collection;
    class Object;

    class IDefinition
    {
    public:
        IDefinition(std::string webidltext, webidl2cpp::Settings settings);

        struct Current
        {
            std::string top;
            std::string inheritances;
            std::string public_zone;
            std::string private_zone;
            std::string bottom;
            std::string source;
            std::string copy; // Конструктор копирования
            std::string copy_end;

            Object* parent;

            bool hasCopyConstructor();
            bool hasInheritance();
        };
        struct Overall
        {
            std::string header_top;
            std::string header_bottom;
            std::string header;
            std::string source_top;
            std::string source_bottom;
            std::string source;
        };

        void push();

        Interface* findInterface(std::string name);
        Dictonary* findDictonary(std::string name);

        Current& current();

    private:
        webidl2cpp::Settings mSettings;
        std::string mText;
        Current mCurrent;
        Overall mOverall;
        //InterfaceList mInterfaces;
        //DictonaryList mDictonaries;
    };
}
