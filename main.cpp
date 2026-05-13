#include "CPPclassunit.h"
#include "CPPmethodunit.h"
#include "CPPprintoperatorunit.h"
std::string generateProgram() {
    CPPClassUnit myClass( "MyClass" );
    myClass.add(
        std::make_shared< CPPMethodUnit >( "testFunc1", "void", 0 ),
        CPPClassUnit::PUBLIC
        );
    myClass.add(
        std::make_shared< CPPMethodUnit >( "testFunc2", "void", CPPMethodUnit::STATIC ),
        CPPClassUnit::PRIVATE
        );
    myClass.add(
        std::make_shared< CPPMethodUnit >( "testFunc3", "void", CPPMethodUnit::VIRTUAL |
                                                              CPPMethodUnit::CONST ),
        CPPClassUnit::PUBLIC
        );
    auto method = std::make_shared< CPPMethodUnit >( "testFunc4", "void",
                                               CPPMethodUnit::STATIC );
    method->add( std::make_shared< CPPPrintOperatorUnit >( R"(Hello, world!\n)" ) );
    myClass.add( method, CPPClassUnit::PROTECTED );
    return myClass.compile();
}

int main() {
    std::cout << generateProgram() << std::endl;
    return 0;
}
