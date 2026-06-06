#ifndef METHODUNIT_H
#define METHODUNIT_H
#include "unit.h"
#include <vector>
#include "modifiers/methodmodifier.h"
class MethodUnit : public Unit {
public:
    MethodUnit( const std::string& name, const std::string& returnType, Flags flags ) :
        m_name( name ), m_returnType( returnType ), m_flags( flags ) { }
    virtual void add( const std::shared_ptr< Unit >& unit, Flags /* flags */ = 0 ) override = 0;
    virtual std::string compile( unsigned int level = 0 ) const override = 0;
    Flags getFlags() const {return m_flags;}
    virtual bool isAbstract() const
    {
        return false;
    }
protected:
    std::string m_name;
    std::string m_returnType;
    Flags m_flags;
    std::vector< std::shared_ptr< Unit > > m_body;
};
#endif // METHODUNIT_H
