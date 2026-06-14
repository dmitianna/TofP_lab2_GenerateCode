#include "factories.h"

std::string generateProgram(AbstractFactory& factory) {
    auto myClass = factory.CreateClassUnit("MyClass");
    myClass->add(factory.CreateMethodUnit("testFunc1", "void", 0),AccessModifier::PUBLIC);
    myClass->add(
        factory.CreateMethodUnit("testFunc2","void",MethodModifier::STATIC),AccessModifier::PRIVATE);

    myClass->add(factory.CreateMethodUnit("testFunc3","void",
           MethodModifier::VIRTUAL | MethodModifier::CONST), AccessModifier::PUBLIC);
    auto method = factory.CreateMethodUnit("testFunc4","void",MethodModifier::STATIC);

    method->add(factory.CreatePrintOperatorUnit(R"(Hello, world!\n)"));

    myClass->add(method, AccessModifier::PROTECTED);

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
