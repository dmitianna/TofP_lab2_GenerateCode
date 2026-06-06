#ifndef CSMETHODUNIT_H
#define CSMETHODUNIT_H
#include "methodunit.h"
#include <vector>
class CSMethodUnit : public MethodUnit
{
public:
    CSMethodUnit( const std::string& name, const std::string& returnType, Flags flags = 0) : MethodUnit(name, returnType, flags) { }

    void add( const std::shared_ptr< Unit >& unit, Flags /* flags */ = 0 ) override
    {
        if(m_flags & MethodModifier::ABSTRACT) return;
        m_body.push_back( unit );
    }
    std::string compile( unsigned int level = 0 ) const override
    {
        if((m_flags & MethodModifier::ABSTRACT) && (m_flags & MethodModifier::STATIC)) {
            throw std::runtime_error("C# method cannot be both abstract and static");
        }

        if((m_flags & MethodModifier::ABSTRACT) && (m_flags & MethodModifier::SEALED)) {
            throw std::runtime_error("C# method cannot be both abstract and sealed");
        }

        if((m_flags & MethodModifier::VIRTUAL) && (m_flags & MethodModifier::STATIC)) {
            throw std::runtime_error("C# method cannot be both virtual and static");
        }

        std::string result = generateShift(level);

        if(m_flags & MethodModifier::ABSTRACT)
            result += "abstract ";

        if(m_flags & MethodModifier::EXTERN)
            result += "extern ";

        if((m_flags & MethodModifier::STATIC) && !(m_flags & MethodModifier::ABSTRACT))
            result += "static ";
        else if(m_flags & MethodModifier::VIRTUAL)
            result += "virtual ";

        if((m_flags & MethodModifier::SEALED) && !(m_flags & MethodModifier::ABSTRACT))
            result += "sealed ";

        result += m_returnType + ' ';
        result += m_name + "() ";

        if((m_flags & MethodModifier::ABSTRACT) || (m_flags & MethodModifier::EXTERN)) {
            result += ";\n";
            return result;
        }
        result += "{\n";
        for(auto it = m_body.begin(); it != m_body.end(); ++it) {
            result += (*it)->compile(level + 1);
        }

        result += generateShift(level) + "}\n";

        return result;
    }
    bool isAbstract() const override
    {
        return m_flags & MethodModifier::ABSTRACT;
    }
};
#endif // CSMETHODUNIT_H
