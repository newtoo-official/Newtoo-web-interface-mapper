#include "settings.h"

namespace NewtooWebInterfaceMapper
{
    Settings::Settings() : mNamespace(initialNamespace),
        mExceptionTemplateClass(initialExceptionTemplateClass),
        mStringPointerClass(initialStringPointerClass),
        mInterfaceLanguage(initialInterfaceLanguage),
        mSequence(initialSequence),
        mTimeStamp(initialTimeStamp),
        mExceptionOrVoid(initialExceptionOrVoid)
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
    StringItem Settings::getTimeStamp() const
    {
        return mTimeStamp;
    }
    StringItem Settings::getExceptionOrVoid() const
    {
        return mExceptionOrVoid;
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
             std::string aTimeStamp,
             std::string aExceptionOrVoid)
    {
        mNamespace = aNamespace;
        mExceptionTemplateClass = aExceptionTemplateClass;
        mStringPointerClass = aStringPointerClass;
        mInterfaceLanguage = aInterfaceLanguage;
        mSequence = aSequence;
        mTimeStamp = aTimeStamp;
        mExceptionOrVoid = aExceptionOrVoid;
    }

    void Settings::resetDefaults()
    {
        mNamespace = initialNamespace;
        mExceptionTemplateClass = initialExceptionTemplateClass;
        mStringPointerClass = initialStringPointerClass;
        mInterfaceLanguage = initialInterfaceLanguage;
        mSequence = initialSequence;
        mTimeStamp = initialTimeStamp;
        mExceptionOrVoid = initialExceptionOrVoid;
    }
}
