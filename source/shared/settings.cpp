#include "settings.h"

namespace NewtooWebInterfaceMapper
{
    Settings::Settings() : mNamespace(initialNamespace()),
        mExceptionTemplateClass(initialExceptionTemplateClass()),
        mStringPointerClass(initialStringPointerClass()),
        mInterfaceLanguage(initialInterfaceLanguage())
    {}

    StringItem Settings::getNamespace() const
    {
        return mNamespace;
    }
    StringItem Settings::getExceptionTemplateClass() const
    {
        return mExceptionTemplateClass;
    }
    StringItem Settings::getStringPointerClass() const
    {
        return mStringPointerClass;
    }
    StringItem Settings::getInterfaceLanguage() const
    {
        return mInterfaceLanguage;
    }

    bool Settings::hasNamespace()
    {
        if(mNamespace == initialNamespace())
            return false;

        else return true;
    }

    std::string Settings::initialNamespace()
    {
        return "";
    }
    std::string Settings::initialExceptionTemplateClass()
    {
        return "RaisesException";
    }
    std::string Settings::initialStringPointerClass()
    {
        return "DOMStringOrNull";
    }
    std::string Settings::initialInterfaceLanguage()
    {
        return "English, US";
    }

    void Settings::set(std::string aNamespace,
             std::string aExceptionTemplateClass,
             std::string aStringPointerClass,
             std::string aInterfaceLanguage)
    {
        mNamespace = aNamespace;
        mExceptionTemplateClass = aExceptionTemplateClass;
        mStringPointerClass = aStringPointerClass;
        mInterfaceLanguage = aInterfaceLanguage;
    }

    void Settings::resetDefaults()
    {
        mNamespace = initialNamespace();
        mExceptionTemplateClass = initialExceptionTemplateClass();
        mStringPointerClass = initialStringPointerClass();
        mInterfaceLanguage = initialInterfaceLanguage();
    }
}
