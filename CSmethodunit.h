#ifndef CSMETHODUNIT_H
#define CSMETHODUNIT_H
#include "methodunit.h"
#include <vector>
class CSMethodUnit : public MethodUnit
{
public:
    enum Modifier {
        STATIC   = MethodUnit::STATIC,
        VIRTUAL  = MethodUnit::VIRTUAL,
        SEALED   = 1 << 3,
        ABSTRACT = 1 << 4,
        EXTERN   = 1 << 5
    };
public:
    CSMethodUnit( const std::string& name, const std::string& returnType, Flags flags = 0) : MethodUnit(name, returnType, flags) { }

    void add( const std::shared_ptr< Unit >& unit, Flags /* flags */ = 0 ) override
    {
        if(m_flags & ABSTRACT) return;
        m_body.push_back( unit );
    }
    std::string compile( unsigned int level = 0 ) const override
    {
        if((m_flags & ABSTRACT) && (m_flags & STATIC)) {
            throw std::runtime_error("C# method cannot be both abstract and static");
        }

        if((m_flags & ABSTRACT) && (m_flags & SEALED)) {
            throw std::runtime_error("C# method cannot be both abstract and sealed");
        }

        if((m_flags & VIRTUAL) && (m_flags & STATIC)) {
            throw std::runtime_error("C# method cannot be both virtual and static");
        }

        std::string result = generateShift(level);

        if(m_flags & ABSTRACT)
            result += "abstract ";

        if(m_flags & EXTERN)
            result += "extern ";

        if((m_flags & STATIC) && !(m_flags & ABSTRACT))
            result += "static ";
        else if(m_flags & VIRTUAL)
            result += "virtual ";

        if((m_flags & SEALED) && !(m_flags & ABSTRACT))
            result += "sealed ";

        result += m_returnType + ' ';
        result += m_name + "() ";

        if((m_flags & ABSTRACT) || (m_flags & EXTERN)) {
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
};
#endif // CSMETHODUNIT_H
