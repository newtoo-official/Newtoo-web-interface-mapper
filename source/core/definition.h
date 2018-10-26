#pragma once

#include <string>

#define nullstr ""

namespace NewtooWebInterfaceMapper_core
{
    class IDL;

    enum DefinitionType
    {
        INTERFACE,
        DICTONARY,
        ENUMERATION,
        TYPEDEFINE,
        IMPLEMENTS,
        INCLUDES
    };

    class Definition
    {
    public:
        Definition* create(std::string text, IDL* idl);
        DefinitionType type() const;

        IDL* idl() const;

        virtual std::string serializeHeader();
        virtual std::string serializeSource();
        virtual void cascade();

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

    protected:
        Definition(DefinitionType aType, IDL* aIdl, std::string decl);

    private:

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

        std::string mCopyConstructorStart;           // ex. Object::Object(Object& ref)
        std::string mCopyConstructorInitFields;      // ex. : mParent(0)
        std::string mCopyConstructorEnd;             // ex. {}
        std::string mHeaderStart;                    // ex. class Object
        std::string mHeaderInherit;                  // ex. : public AbstractObject
        std::string mHeaderPublic;                   // ex. { public: Object* parent() const;
        std::string mHeaderPublicAppendix;           // ex. void run();
        std::string mHeaderPrivate;                  // ex. private: Object* mParent;
        std::string mHeaderEnd;                      // ex. };
        std::string mSource;                         // ex. Object* Object::parent const
                                                     //     { return mParent;}
                                                     //     void Object::run()
                                                     //     {}

        std::string generateHeader();
        /*
            mCopyConstructorStart + mCopyConstructorInitFields + mCopyConstructorEnd + mSource
        */

        std::string generateSource();
        /*
            mHeaderStart + mHeaderInherit + mHeaderPublic + mHeaderPublicAppendix + mHeaderPrivate
            + mHeaderEnd
        */

        std::string append(std::string); // += mHeaderPublicAppendix
        /*
            Нужен, чтобы объединять все частичные определения воедино через DefinitionList::cascade()
            Находин он нужное определение через DefinitionList::findDefinition(...);
         */

        DefinitionType mType;
        IDL* mIdl;
    };
}
