#ifndef JAVAMETHODUNIT_H
#define JAVAMETHODUNIT_H
#include "methodunit.h"
#include <vector>
class JAVAMethodUnit : public MethodUnit
{
public:
    JAVAMethodUnit( const std::string& name, const std::string& returnType, Flags flags ) : MethodUnit(name, returnType, flags) { }

    void add( const std::shared_ptr< Unit >& unit, Flags /* flags */ = 0 ) override
    {
        if(m_flags & MethodModifier::ABSTRACT) return;
        m_body.push_back( unit );
    }
    std::string compile( unsigned int level = 0 ) const override
    {
        if((m_flags & MethodModifier::ABSTRACT) && (m_flags & MethodModifier::FINAL)) {
            throw std::runtime_error("Java method cannot be both abstract and final");
        }

        if((m_flags & MethodModifier::ABSTRACT) && (m_flags & MethodModifier::STATIC)) {
            throw std::runtime_error("Java method cannot be both abstract and static");
        }

        if(m_flags & MethodModifier::VIRTUAL) {
            throw std::runtime_error("Java does not support virtual methods");
        }

        if(m_flags & MethodModifier::CONST) {
            throw std::runtime_error("Java does not support const methods");
        }

        if((m_flags & MethodModifier::ABSTRACT) && !m_body.empty()) {
            throw std::runtime_error("Abstract Java method cannot have body");
        }
        std::string result = generateShift( level );
        if(m_flags & MethodModifier::ABSTRACT)
            result += "abstract ";

        if(m_flags & MethodModifier::STATIC)
            result += "static ";

        if(m_flags & MethodModifier::FINAL)
            result += "final ";

        result += m_returnType + " ";
        result += m_name + "()";

        if(m_flags & MethodModifier::ABSTRACT) {
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
    bool isAbstract() const override
    {
        return m_flags & MethodModifier::ABSTRACT;
    }
};
#endif // JAVAMETHODUNIT_H
