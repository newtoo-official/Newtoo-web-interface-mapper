#pragma once

#include <string>

namespace NewtooWebInterfaceMapper
{
    typedef std::string StringItem;

    class Settings
    {
    public:
        Settings();

        StringItem getNamespace() const;
        StringItem getExceptionTemplateClass() const;
        StringItem getStringPointerClass() const;
        StringItem getInterfaceLanguage() const;

        bool hasNamespace();

        static std::string initialNamespace();
        static std::string initialExceptionTemplateClass();
        static std::string initialStringPointerClass();
        static std::string initialInterfaceLanguage();

        void set(std::string aNamespace,
                 std::string aExceptionTemplateClass,
                 std::string aStringPointerClass,
                 std::string aInterfaceLanguage);

        void resetDefaults();

    private:
        StringItem mNamespace,
                   mExceptionTemplateClass,
                   mStringPointerClass,
                   mInterfaceLanguage;
    };
}
