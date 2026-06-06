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

int main() {
    //std::cout << generateProgram() << std::endl;
    //testCs();

    CppGeneratorFactory cppFactory;
    CSGeneratorFactory csFactory;
    JAVAGeneratorFactory javaFactory;
    std::cout << generateProgram(cppFactory) << std::endl;
    std::cout << generateProgram(csFactory) << std::endl;
    //std::cout << generateProgram(javaFactory) << std::endl;

    return 0;
}
