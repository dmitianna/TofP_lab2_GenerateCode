#include "CPPclassunit.h"
#include "CPPmethodunit.h"
#include "CPPprintoperatorunit.h"
#include <assert.h>
#include "CSclassunit.h"
#include "CSmethodunit.h"
#include "CSprintoperatorunit.h"
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

void testCs() {

    CSMethodUnit test1("test1", "void");
    std::cout << test1.compile()<< std::endl;

    CSMethodUnit test2("test2", "void", CSMethodUnit::ABSTRACT);
    std::cout << test2.compile()<< std::endl;

    CSMethodUnit test3("test3", "void", CSMethodUnit::SEALED);
    std::cout << test3.compile()<< std::endl;

    CSMethodUnit test4("test4", "void", CSMethodUnit::STATIC);
    std::cout << test4.compile()<< std::endl;

    CSMethodUnit test5("test5", "void", CSMethodUnit::VIRTUAL);
    std::cout << test5.compile()<< std::endl;

    CSMethodUnit test6("test6", "void", CSMethodUnit::CONST);
    std::cout << test6.compile()<< std::endl;

    CSMethodUnit test7("test7", "void", CSMethodUnit::READONLY);
    std::cout << test7.compile()<< std::endl;


    CSMethodUnit test8("test8", "void", CSMethodUnit::ABSTRACT | CSMethodUnit::CONST);
    std::cout << test8.compile()<< std::endl;

    CSMethodUnit test9("test9", "void", CSMethodUnit::STATIC | CSMethodUnit::VIRTUAL);
    std::cout << test9.compile()<< std::endl;

    CSMethodUnit test10("test10", "void",CSMethodUnit::SEALED | CSMethodUnit::READONLY);
    std::cout << test10.compile()<< std::endl;
}

int main() {
    //std::cout << generateProgram() << std::endl;
    testCs();
    return 0;
}
