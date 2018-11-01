#pragma once

#include <string>

namespace NewtooWebInterfaceMapper
{
    typedef std::string StringItem;

    const char initialNamespace[] = "";
    const char initialExceptionTemplateClass[] = "RaisesException";
    const char initialStringPointerClass[] = "DOMStringOrNull";
    const char initialInterfaceLanguage[] = "English, US";
    const char initialSequence[] = "Sequence";
    const char initialTimeStamp[] = "unsigned long long";
    const char initialExceptionOrVoid[] = "ExceptionOrVoid";
    const char initialArray[] = "Array";

    class Settings
    {
    public:
        Settings();

        StringItem getNamespace() const;
        StringItem getExceptionTemplateClass() const;
        StringItem getStringPointerClass() const;
        StringItem getInterfaceLanguage() const;
        StringItem getSequence() const;
        StringItem getTimeStamp() const;
        StringItem getExceptionOrVoid() const;
        StringItem getArray() const;

        bool hasNamespace();

        void set(std::string aNamespace,
                 std::string aExceptionTemplateClass,
                 std::string aStringPointerClass,
                 std::string aInterfaceLanguage,
                 std::string aSequence,
                 std::string aTimeStamp,
                 std::string aExceptionOrVoid,
                 std::string aArray);

        void resetDefaults();

    private:
        StringItem mNamespace,
                   mExceptionTemplateClass,
                   mStringPointerClass,
                   mInterfaceLanguage,
                   mSequence,
                   mTimeStamp,
                   mExceptionOrVoid,
                   mArray;
    };
}
