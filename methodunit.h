#ifndef METHODUNIT_H
#define METHODUNIT_H
#include "unit.h"
#include <vector>
class MethodUnit : public Unit {
public:
    enum Modifier {
        STATIC = 1,
        CONST = 1 << 1,
        VIRTUAL = 1 << 2
    };
public:
    MethodUnit( const std::string& name, const std::string& returnType, Flags
                                                                           flags ) :
        m_name( name ), m_returnType( returnType ), m_flags( flags ) { }
    void add( const std::shared_ptr< Unit >& unit, Flags /* flags */ = 0 ) override {
        m_body.push_back( unit );
    }
    std::string compile( unsigned int level = 0 ) const override {
        std::string result = generateShift( level );
        if( m_flags & STATIC ) {
            result += "static ";
        } else if( m_flags & VIRTUAL ) {
            result += "virtual ";
        }
        result += m_returnType + " ";
        result += m_name + "()";
        if( m_flags & CONST ) {
            result += " const";
        }
        result += " {\n";
        for( const auto& b : m_body ) {
            result += b->compile( level + 1 );
        }
        result += generateShift( level ) + "}\n";
        return result;
    }
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
