#ifndef CSCLASSUNIT_H
#define CSCLASSUNIT_H
#include "classunit.h"
#include "methodunit.h"
#include <vector>
class CSClassUnit : public ClassUnit
{
    enum CSAccesModifier : Flags {
        PUBLIC = AccessModifier::PUBLIC,
        PROTECTED = AccessModifier::PROTECTED,
        PRIVATE = AccessModifier::PRIVATE,
        PRIVATE_PROTECTED,
        FILE,
        INTERNAL,
        PROTECTED_INTERNAL
    };
    static const std::vector<std::string> CS_ACCESS_MODIFIERS;
public:
    explicit CSClassUnit(const std::string &name) : ClassUnit(name)
    {  m_fields.resize(ACCESS_MODIFIERS.size() + CS_ACCESS_MODIFIERS.size());}

    void add( const std::shared_ptr< Unit >& unit, Flags flags ) override
    {
        size_t accessModifier = AccessModifier::PUBLIC;

        if(flags < (ACCESS_MODIFIERS.size() + CS_ACCESS_MODIFIERS.size())) {
            accessModifier = flags;
        }

        auto method =std::dynamic_pointer_cast<MethodUnit>(unit);
        if(method && method->isAbstract())
        {
            isAbstract = true;
        }
        m_fields[accessModifier].push_back(unit);
    }

    std::string compile( unsigned int level = 0 ) const override
    {
        std::string result = generateShift(level);
        if (isAbstract) {
            result += "abstract ";
        }

        result += "class " + m_name;
        result += " {\n";

        size_t accessModifiersSize = ACCESS_MODIFIERS.size() + CS_ACCESS_MODIFIERS.size();
        for(size_t i = 0; i < accessModifiersSize; ++i) {
            if(m_fields[i].empty()) {
                continue;
            }
            for (const auto &field : m_fields[i]) {
                std::string access_modifier;

                if (i > ACCESS_MODIFIERS.size() - 1) {
                    int custom_index = i - ACCESS_MODIFIERS.size();
                    access_modifier = CS_ACCESS_MODIFIERS[custom_index];
                } else {
                    access_modifier = ACCESS_MODIFIERS[i];
                }
                std::string compiled = field->compile(level + 1);
                auto pos = compiled.find_first_not_of(' ');
                if (pos != std::string::npos) {
                    compiled.insert(pos, access_modifier + " ");
                }
                result += compiled;
            }
            result += "\n";
        }
        result += generateShift(level) + "}\n";
        return result;
    }

private:
    bool isAbstract = false;
};
const std::vector<std::string> CSClassUnit::CS_ACCESS_MODIFIERS = {"private protected", "file", "internal", "protected internal"};
#endif // CSCLASSUNIT_H
