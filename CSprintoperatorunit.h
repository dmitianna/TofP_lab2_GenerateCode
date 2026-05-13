#ifndef CSPRINTOPERATORUNIT_H
#define CSPRINTOPERATORUNIT_H
#include "printoperatorunit.h"
class CSPrintOperatorUnit : public PrintOperatorUnit {
public:
    explicit CSPrintOperatorUnit( const std::string& text ) : PrintOperatorUnit(text) { }
    std::string compile( unsigned int level = 0 ) const override
    {
        return generateShift( level ) + "printf( \"" + m_text + "\" );\n";
    }
};
#endif // CSPRINTOPERATORUNIT_H
