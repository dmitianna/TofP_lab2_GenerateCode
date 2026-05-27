#include "factories.h"

std::string generateProgram(AbstractFactory& factory) {
    auto myClass = factory.CreateClassUnit("MyClass");
    myClass->add(factory.CreateMethodUnit("testFunc1", "void", 0),ClassUnit::PUBLIC);
    myClass->add(
        factory.CreateMethodUnit("testFunc2","void",MethodUnit::STATIC),ClassUnit::PRIVATE);

    myClass->add(factory.CreateMethodUnit("testFunc3","void",
            MethodUnit::VIRTUAL | MethodUnit::CONST), ClassUnit::PUBLIC);
    auto method = factory.CreateMethodUnit("testFunc4","void",MethodUnit::STATIC);

    method->add(factory.CreatePrintOperatorUnit(R"(Hello, world!\n)"));

    myClass->add(method, ClassUnit::PROTECTED);

    return myClass->compile();
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
    //testCs();

    CppGeneratorFactory cppFactory;
    CSGeneratorFactory csFactory;
    JAVAGeneratorFactory javaFactory;
    std::cout << generateProgram(csFactory)<< std::endl;

    return 0;
}
