#pragma once

#include <string>

namespace NewtooWebInterfaceMapper
{
    typedef std::string StringItem;

    const char InitialNamespace[] = "";
    const char InitialExceptionTemplateClass[] = "RaisesException";
    const char InitialStringPointerClass[] = "DOMStringOrNull";
    const char InitialInterfaceLanguage[] = "English, US";
    const char InitialSequence[] = "Sequence";
    const char InitialExceptionOrVoid[] = "ExceptionOrVoid";
    const char InitialArray[] = "Array";
    const bool InitialUseGlobalEnumerations = false;

    class Settings
    {
    public:
        Settings();

        StringItem getNamespace() const;
        StringItem getExceptionTemplateClass() const;
        StringItem getStringPointerClass() const;
        StringItem getInterfaceLanguage() const;
        StringItem getSequence() const;
        StringItem getExceptionOrVoid() const;
        StringItem getArray() const;
        bool getUseGlobalEnumerations() const;

        bool useGlobalEnumerations() const;

        bool hasNamespace();

        void set(std::string aNamespace,
                 std::string aExceptionTemplateClass,
                 std::string aStringPointerClass,
                 std::string aInterfaceLanguage,
                 std::string aSequence,
                 std::string aExceptionOrVoid,
                 std::string aArray,
                 bool aUseGlobalEnumerations);

        void resetDefaults();

    private:
        StringItem mNamespace,
                   mExceptionTemplateClass,
                   mStringPointerClass,
                   mInterfaceLanguage,
                   mSequence,
                   mExceptionOrVoid,
                   mArray;
        bool mUseGlobalEnumerations;
    };
}
