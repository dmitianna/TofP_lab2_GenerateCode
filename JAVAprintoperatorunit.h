#ifndef JAVAPRINTOPERATORUNIT_H
#define JAVAPRINTOPERATORUNIT_H
#include "printoperatorunit.h"
class JAVAPrintOperatorUnit : public PrintOperatorUnit {
public:
    explicit JAVAPrintOperatorUnit( const std::string& text ) : PrintOperatorUnit(text) { }
    std::string compile( unsigned int level = 0 ) const override
    {
        return generateShift( level ) + "System.out.println(\"" + m_text + "\");\n";
    }
};
#endif // JAVAPRINTOPERATORUNIT_H
