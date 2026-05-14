#ifndef CSCLASSUNIT_H
#define CSCLASSUNIT_H
#include "classunit.h"
#include "CsMethodUnit.h"
#include <vector>
class CSClassUnit : public ClassUnit
{
    enum CSAccesModifier : Flags {
        PUBLIC = AccessModifier::PUBLIC,
        PROTECTED = AccessModifier::PROTECTED,
        PRIVATE = AccessModifier::PRIVATE,
        PRIVATE_PROTECTED,
        FILE,
        INTERNAL,
        PROTECTED_INTERNAL
    };
    static const std::vector<std::string> CS_ACCESS_MODIFIERS;
public:
    explicit CSClassUnit(const std::string &name) : ClassUnit(name)
    {  m_fields.resize(ACCESS_MODIFIERS.size() + CS_ACCESS_MODIFIERS.size());}

    void add( const std::shared_ptr< Unit >& unit, Flags flags ) override
    {
        if(!isAbstract & static_cast<bool>(CSMethodUnit::ABSTRACT)) {
            isAbstract = true;
        }

        int accessModifier = AccessModifier::PUBLIC;

        if(flags < (ACCESS_MODIFIERS.size() + CS_ACCESS_MODIFIERS.size())) {
            accessModifier = flags;
        }

        m_fields[accessModifier].push_back(unit);
    }

    std::string compile( unsigned int level = 0 ) const override
    {
        return {};
    }

private:
    bool isAbstract = false;
};
const std::vector<std::string> CSClassUnit::CS_ACCESS_MODIFIERS = {"private protected", "file", "internal", "protected internal"};
#endif // CSCLASSUNIT_H
