#ifndef CLASSUNIT_H
#define CLASSUNIT_H
#include "unit.h"
#include <vector>
#include "modifiers/accessmodifier.h"
class ClassUnit : public Unit
{
public:
    static const std::vector<std::string> ACCESS_MODIFIERS;
public:
    explicit ClassUnit( const std::string& name ) : m_name( name ) {
        m_fields.resize(ACCESS_MODIFIERS.size());
    }

    virtual void add(const std::shared_ptr<Unit>& unit, Flags flags) override = 0;
    virtual std::string compile(unsigned int level = 0) const override = 0;
protected:
    std::string m_name;
    using Fields = std::vector< std::shared_ptr< Unit > >;
    std::vector< Fields > m_fields;
};
const std::vector<std::string> ClassUnit::ACCESS_MODIFIERS = {"public", "protected", "private"};
#endif // CLASSUNIT_H
