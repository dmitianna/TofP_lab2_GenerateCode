#ifndef JAVAMETHODUNIT_H
#define JAVAMETHODUNIT_H
#include "methodunit.h"
#include <vector>
class JAVAMethodUnit : public MethodUnit
{
public:
    enum Modifier {
        STATIC = 1,
        FINAL = 1 << 1,
        ABSTRACT = 1 << 2
    };
public:
    JAVAMethodUnit( const std::string& name, const std::string& returnType, Flags flags ) : MethodUnit(name, returnType, flags) { }

    void add( const std::shared_ptr< Unit >& unit, Flags /* flags */ = 0 ) override
    {
        if(m_flags & ABSTRACT) return;
        m_body.push_back( unit );
    }
    std::string compile( unsigned int level = 0 ) const override
    {
        if((m_flags & ABSTRACT) && (m_flags & FINAL)) {
            throw std::runtime_error("Java method cannot be both abstract and final");
        }

        if((m_flags & ABSTRACT) && (m_flags & STATIC)) {
            throw std::runtime_error("Java method cannot be both abstract and static");
        }

        std::string result = generateShift( level );
        if(m_flags & ABSTRACT)
            result += "abstract ";

        if(m_flags & STATIC)
            result += "static ";

        if(m_flags & FINAL)
            result += "final ";

        result += m_returnType + " ";
        result += m_name + "()";

        if(m_flags & ABSTRACT) {
            result += ";\n";
            return result;
        }
        result += " {\n";
        for( const auto& b : m_body ) {
            result += b->compile( level + 1 );
        }
        result += generateShift( level ) + "}\n";
        return result;
    }
};
#endif // JAVAMETHODUNIT_H
