#ifndef JAVACLASSUNIT_H
#define JAVACLASSUNIT_H
#include "classunit.h"
#include <vector>
class JAVAClassUnit : public ClassUnit
{

public:
    explicit JAVAClassUnit(const std::string &name) : ClassUnit(name)
    { }

    void add( const std::shared_ptr< Unit >& unit, Flags flags ) override
    {
        int accessModifier = PRIVATE;
        if( flags < ACCESS_MODIFIERS.size() ) {
            accessModifier = flags;
        }
        m_fields[ accessModifier ].push_back( unit );
    }

    std::string compile( unsigned int level = 0 ) const override
    {
        std::string result = generateShift( level ) + "class " + m_name + " {\n";
        for( size_t i = 0; i < ACCESS_MODIFIERS.size(); ++i ) {
            if( m_fields[ i ].empty() ) {
                continue;
            }
            for( const auto& f : m_fields[ i ] ) {
                std::string compiled = f->compile(level + 1);
                compiled.insert(compiled.find_first_not_of(' '),ACCESS_MODIFIERS[i] + " ");
                result += compiled;
            }
            result += "\n";
        }
        result += generateShift( level ) + "}\n";
        return result;
    }
};

#endif // JAVACLASSUNIT_H
