#pragma once

#include "definition.h"
#include "extattrmap.h"
#include "interfaceinner.h"

namespace NewtooWebInterfaceMapper_core
{
    class Interface : public Definition
    {
    public:
        Interface(IDL* aIdl, std::string decl);

        std::string& interfaceName();

        std::string& copyConstructorStart();
        std::string& copyConstructorInitFields();
        std::string& copyConstructorInitFieldsAppendix();
        std::string& copyConstructorEnd();
        std::string& headerStart();
        std::string& headerInherit();
        std::string& headerPublic();
        std::string& headerPublicPrefix();
        std::string& headerPublicAppendix();
        std::string& headerPrivate();
        std::string& headerPrivateAppendix();
        std::string& headerEnd();
        std::string& source();

        std::string serializeHeader() override;
        /*
            mHeaderStart + mHeaderInherit + headerPublicPrefix() + mHeaderPublic + mHeaderPublicAppendix
            + mHeaderPrivate + mHeaderPrivateAppendix + mHeaderEnd
        */

        std::string serializeSource() override;
        /*
            mCopyConstructorStart + mCopyConstructorInitFields + mCopyConstructorInitFieldsAppendix
            + mCopyConstructorEnd + mSource
        */

        std::string serializeHeader_Interface();
        std::string serializeSource_Interface();

        void cascade() override;

        void append(std::string partialHeaderPublic, std::string partialHeaderPrivate,
                    std::string partialCopyConstructorInitFields, std::string partialSource);
        /*
            Нужен, чтобы объединять все частичные определения воедино через DefinitionList::cascade()
            Находин он нужное определение через DefinitionList::findDefinition(...);
        */

        void appendUnit(InterfaceUnit unit);
        /*
            Сделать этот класс хостом атрибута. Это означает, что для атрибута будет создано
            приватное поле, которое он будет возращать.
        */

        bool isPartial() const;

        std::string includeDirective(); // ex. #include "Object.h"

        void modifySource(std::string& source) override;

    protected:
        void appendMemberToCopyConstructor(std::string member);

        /*
            For example:

            interface Object : AbstractObject
            {
                readonly attribute Object? parent;
            };
            partially inteface Object
            {
                void run();
            };
        */

        std::string mInterfaceName;

        std::string mCopyConstructorStart;              // ex. Object::Object(Object& ref)
        std::string mCopyConstructorInitFields;         // ex. : mParent(0)
        std::string mCopyConstructorInitFieldsAppendix;
        std::string mCopyConstructorEnd;                // ex. {}
        std::string mHeaderStart;                       // ex. class Object
        std::string mHeaderInherit;                     // ex. : public AbstractObject
        std::string mHeaderPublic;                      // ex. Object* parent() const;
        std::string mHeaderPublicAppendix;              // ex. void run();
        std::string mHeaderPrivate;                     // ex. private: Object* mParent;
        std::string mHeaderPrivateAppendix;
        std::string mHeaderEnd;                         // ex. };
        std::string mSource;                            // ex. Object* Object::parent const
                                                        //     { return mParent;}
                                                        //     void Object::run()
                                                        //     {}

        std::string mHeaderPublicPrefix;

        bool mIsPartial;
    };
}
