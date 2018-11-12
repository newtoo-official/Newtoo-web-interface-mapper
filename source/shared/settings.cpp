#include "settings.h"

namespace NewtooWebInterfaceMapper
{
    Settings::Settings() : mNamespace(InitialNamespace),
        mExceptionTemplateClass(InitialExceptionTemplateClass),
        mStringPointerClass(InitialStringPointerClass),
        mInterfaceLanguage(InitialInterfaceLanguage),
        mSequence(InitialSequence),
        mExceptionOrVoid(InitialExceptionOrVoid),
        mArray(InitialArray),
        mUseGlobalEnumerations(InitialUseGlobalEnumerations)
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
    bool Settings::getUseGlobalEnumerations() const
    {
        return mUseGlobalEnumerations;
    }

    bool Settings::useGlobalEnumerations() const
    {
        return mUseGlobalEnumerations;
    }

    bool Settings::hasNamespace()
    {
        if(mNamespace == InitialNamespace)
            return false;

        else return true;
    }

    void Settings::set(std::string aNamespace,
             std::string aExceptionTemplateClass,
             std::string aStringPointerClass,
             std::string aInterfaceLanguage,
             std::string aSequence,
             std::string aExceptionOrVoid,
             std::string aArray,
             bool aUseGlobalEnumerations)
    {
        mNamespace = aNamespace;
        mExceptionTemplateClass = aExceptionTemplateClass;
        mStringPointerClass = aStringPointerClass;
        mInterfaceLanguage = aInterfaceLanguage;
        mSequence = aSequence;
        mExceptionOrVoid = aExceptionOrVoid;
        mArray = aArray;
        mUseGlobalEnumerations = aUseGlobalEnumerations;
    }

    void Settings::resetDefaults()
    {
        mNamespace = InitialNamespace;
        mExceptionTemplateClass = InitialExceptionTemplateClass;
        mStringPointerClass = InitialStringPointerClass;
        mInterfaceLanguage = InitialInterfaceLanguage;
        mSequence = InitialSequence;
        mExceptionOrVoid = InitialExceptionOrVoid;
        mArray = InitialArray;
        mUseGlobalEnumerations = InitialUseGlobalEnumerations;
    }
}
