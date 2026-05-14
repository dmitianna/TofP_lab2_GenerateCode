#ifndef CSMETHODUNIT_H
#define CSMETHODUNIT_H
#include "methodunit.h"
#include <vector>
class CSMethodUnit : public MethodUnit
{
public:
    enum Modifier {
        STATIC = 1,
        CONST = 1 << 1,
        VIRTUAL = 1 << 2,
        SEALED = 1 << 3,
        READONLY = 1 << 4,
        ABSTRACT = 1 << 5,
        EXTERN = 1 << 6
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
        std::string result = generateShift(level);

        if(m_flags & ABSTRACT)
            result += "abstract ";

        if((m_flags & STATIC) && !(m_flags & ABSTRACT))
            result += "static ";
        else if(m_flags & VIRTUAL)
            result += "virtual ";

        if((m_flags & SEALED) && !(m_flags & ABSTRACT))
            result += "sealed ";

        if(m_flags & READONLY)
            result += "readonly ";
        else if(m_flags & CONST)
            result += "const ";

        result += m_returnType + ' ';
        result += m_name + "() ";


        result += "{\n";
        for(auto it = m_body.begin(); it != m_body.end(); ++it) {
            result += (*it)->compile(level + 1);
        }

        result += generateShift(level) + "}\n";

        return result;
    }
};
#endif // CSMETHODUNIT_H
