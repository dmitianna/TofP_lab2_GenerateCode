#ifndef JAVACLASSUNIT_H
#define JAVACLASSUNIT_H
#include "classunit.h"
#include "methodunit.h"
#include <vector>
class JAVAClassUnit : public ClassUnit
{
public:
    explicit JAVAClassUnit(const std::string &name, Flags flags = 0) : ClassUnit(name, flags)
    { }

    void add( const std::shared_ptr< Unit >& unit, Flags flags ) override
    {
        size_t accessModifier = AccessModifier::PRIVATE;
        if( flags < ACCESS_MODIFIERS.size() ) {
            accessModifier = flags;
        }
        m_fields[ accessModifier ].push_back( unit );
    }

    std::string compile( unsigned int level = 0 ) const override
    {
        validate();
        std::string result = generateShift(level);
        if(m_flags & ClassModifier::ABSTRACT_CLASS)
        {
            result += "abstract ";
        }
        result += "class " + m_name + " {\n";
        for( size_t i = 0; i < ACCESS_MODIFIERS.size(); ++i ) {
            if( m_fields[ i ].empty() ) {
                continue;
            }
            for( const auto& f : m_fields[ i ] ) {
                std::string compiled = f->compile(level + 1);
                auto pos = compiled.find_first_not_of(' ');
                if(pos != std::string::npos) {
                    compiled.insert(pos, ACCESS_MODIFIERS[i] + " ");
                }
                result += compiled;
            }
            result += "\n";
        }
        result += generateShift( level ) + "}\n";
        return result;
    }

    void validate() const override
    {
        bool hasAbstractMethods = false;

        for(const auto& group : m_fields)
        {
            for(const auto& field : group)
            {
                field->validate();
                auto method =std::dynamic_pointer_cast<MethodUnit>(field);
                if(method &&(method->getFlags() & MethodModifier::ABSTRACT))
                {
                    hasAbstractMethods = true;
                }
            }
        }

        if(hasAbstractMethods && !(m_flags & ClassModifier::ABSTRACT_CLASS))
        {
            throw std::runtime_error("Class containing abstract methods must be abstract");
        }

        if((m_flags & ClassModifier::ABSTRACT_CLASS) && (m_flags & ClassModifier::FINAL_CLASS))
        {
            throw std::runtime_error("Java class cannot be both abstract and final");
        }
    }
};

#endif // JAVACLASSUNIT_H
