#include "settings.h"

namespace NewtooWebInterfaceMapper
{
    Settings::Settings() : mNamespace(initialNamespace),
        mExceptionTemplateClass(initialExceptionTemplateClass),
        mStringPointerClass(initialStringPointerClass),
        mInterfaceLanguage(initialInterfaceLanguage),
        mSequence(initialSequence),
        mExceptionOrVoid(initialExceptionOrVoid),
        mArray(initialArray)
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
    StringItem Settings::getSequence() const
    {
        return mSequence;
    }
    StringItem Settings::getExceptionOrVoid() const
    {
        return mExceptionOrVoid;
    }
    StringItem Settings::getArray() const
    {
        return mArray;
    }

    bool Settings::hasNamespace()
    {
        if(mNamespace == initialNamespace)
            return false;

        else return true;
    }

    void Settings::set(std::string aNamespace,
             std::string aExceptionTemplateClass,
             std::string aStringPointerClass,
             std::string aInterfaceLanguage,
             std::string aSequence,
             std::string aExceptionOrVoid,
             std::string aArray)
    {
        mNamespace = aNamespace;
        mExceptionTemplateClass = aExceptionTemplateClass;
        mStringPointerClass = aStringPointerClass;
        mInterfaceLanguage = aInterfaceLanguage;
        mSequence = aSequence;
        mExceptionOrVoid = aExceptionOrVoid;
        mArray = aArray;
    }

    void Settings::resetDefaults()
    {
        mNamespace = initialNamespace;
        mExceptionTemplateClass = initialExceptionTemplateClass;
        mStringPointerClass = initialStringPointerClass;
        mInterfaceLanguage = initialInterfaceLanguage;
        mSequence = initialSequence;
        mExceptionOrVoid = initialExceptionOrVoid;
        mArray = initialArray;
    }
}
