#ifndef CSCLASSUNIT_H
#define CSCLASSUNIT_H
#include "classunit.h"
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
public:
    explicit CSClassUnit(const std::string &name) : ClassUnit(name)
    { }

    void add( const std::shared_ptr< Unit >& unit, Flags flags ) override
    {
    }

    std::string compile( unsigned int level = 0 ) const override
    {
        return {};
    }
};

#endif // CSCLASSUNIT_H
