#pragma once

#include "definition.h"

namespace NewtooWebInterfaceMapper_core
{
    class Interface : public Definition
    {
    public:
        Interface(IDL* aIdl, std::string decl);

        std::string& interfaceName();

        std::string& copyConstructorStart();
        std::string& copyConstructorInitFields();
        std::string& copyConstructorEnd();
        std::string& headerStart();
        std::string& headerInherit();
        std::string& headerPublic();
        std::string& headerPublicAppendix();
        std::string& headerPrivate();
        std::string& headerEnd();
        std::string& source();

         std::string serializeHeader() override;
        /*
            mCopyConstructorStart + mCopyConstructorInitFields + mCopyConstructorEnd + mSource
        */

        std::string serializeSource() override;
        /*
            mHeaderStart + mHeaderInherit + headerPublicPrefix() + mHeaderPublic + mHeaderPublicAppendix
            + mHeaderPrivate + mHeaderEnd
        */

        void cascade() override;

        void append(std::string partialInner); // mHeaderPublicAppendix += partialInner
        /*
            Нужен, чтобы объединять все частичные определения воедино через DefinitionList::cascade()
            Находин он нужное определение через DefinitionList::findDefinition(...);
        */

        void inviteAttribute(std::string type, std::string name);
        /*
            Сделать этот класс хостом атрибута. Это означает, что для атрибута будет создано
            приватное поле, которое он будет возращать.
        */

        bool isPartial() const;

    protected:
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

        std::string mCopyConstructorStart;           // ex. Object::Object(Object& ref)
        std::string mCopyConstructorInitFields;      // ex. : mParent(0)
        std::string mCopyConstructorEnd;             // ex. {}
        std::string mHeaderStart;                    // ex. class Object
        std::string mHeaderInherit;                  // ex. : public AbstractObject
        std::string mHeaderPublic;                   // ex. Object* parent() const;
        std::string mHeaderPublicAppendix;           // ex. void run();
        std::string mHeaderPrivate;                  // ex. private: Object* mParent;
        std::string mHeaderEnd;                      // ex. };
        std::string mSource;                         // ex. Object* Object::parent const
                                                     //     { return mParent;}
                                                     //     void Object::run()
                                                     //     {}

        std::string headerPublicPrefix();

        bool mIsPartial;
    };
}
