#include <QtTest>

#include "../factories.h"

class GeneratorTests : public QObject
{
    Q_OBJECT

private:

    std::string generateProgram(AbstractFactory& factory)
    {
        auto myClass =
            factory.CreateClassUnit("MyClass");

        myClass->add(
            factory.CreateMethodUnit(
                "testFunc1",
                "void",
                0
                ),
            ClassUnit::PUBLIC
            );

        myClass->add(
            factory.CreateMethodUnit(
                "testFunc2",
                "void",
                MethodUnit::STATIC
                ),
            ClassUnit::PRIVATE
            );

        myClass->add(
            factory.CreateMethodUnit(
                "testFunc3",
                "void",
                MethodUnit::VIRTUAL | MethodUnit::CONST
                ),
            ClassUnit::PUBLIC
            );

        auto method =
            factory.CreateMethodUnit(
                "testFunc4",
                "void",
                MethodUnit::STATIC
                );

        method->add(
            factory.CreatePrintOperatorUnit(
                "Hello, world!"
                )
            );

        myClass->add(
            method,
            ClassUnit::PROTECTED
            );

        return myClass->compile();
    }

private slots:

    void testCPP()
    {
        CppGeneratorFactory factory;

        std::string result = generateProgram(factory);

        QVERIFY(result.find("class MyClass") != std::string::npos);
        QVERIFY(result.find("public:") != std::string::npos);
        QVERIFY(result.find("protected:") != std::string::npos);
        QVERIFY(result.find("private:") != std::string::npos);

        QVERIFY(result.find("void testFunc1()") != std::string::npos);

        QVERIFY(result.find("static void testFunc2()")
                != std::string::npos);

        QVERIFY(result.find("virtual void testFunc3() const")
                != std::string::npos);

        QVERIFY(result.find("printf( \"Hello, world!\" );")
                != std::string::npos);
    }

    void testCS()
    {
        CSGeneratorFactory factory;

        auto myClass =
            factory.CreateClassUnit("MyClass");

        myClass->add(
            factory.CreateMethodUnit(
                "normalMethod",
                "void",
                0
                ),
            ClassUnit::PUBLIC
            );

        myClass->add(
            factory.CreateMethodUnit(
                "abstractMethod",
                "void",
                CSMethodUnit::ABSTRACT
                ),
            ClassUnit::PUBLIC
            );

        auto method =
            factory.CreateMethodUnit(
                "printMethod",
                "void",
                CSMethodUnit::STATIC
                );

        method->add(
            factory.CreatePrintOperatorUnit(
                "Hello C#"
                )
            );

        myClass->add(
            method,
            ClassUnit::PROTECTED
            );

        std::string result = myClass->compile();

        QVERIFY(result.find("abstract class MyClass")
                != std::string::npos);

        QVERIFY(result.find("public void normalMethod()")
                != std::string::npos);

        QVERIFY(result.find("public abstract void abstractMethod() ;")
                    != std::string::npos
                ||
                result.find("public abstract void abstractMethod();")
                    != std::string::npos);

        QVERIFY(result.find("protected static void printMethod()")
                != std::string::npos);

        QVERIFY(result.find("Console.WriteLine(\"Hello C#\")")
                != std::string::npos);
    }

    void testJava()
    {
        JAVAGeneratorFactory factory;

        auto myClass =
            factory.CreateClassUnit("MyClass");

        myClass->add(
            factory.CreateMethodUnit(
                "normalMethod",
                "void",
                0
                ),
            ClassUnit::PUBLIC
            );

        myClass->add(
            factory.CreateMethodUnit(
                "finalMethod",
                "void",
                JAVAMethodUnit::FINAL
                ),
            ClassUnit::PUBLIC
            );

        auto method =
            factory.CreateMethodUnit(
                "printMethod",
                "void",
                JAVAMethodUnit::STATIC
                );

        method->add(
            factory.CreatePrintOperatorUnit(
                "Hello Java"
                )
            );

        myClass->add(
            method,
            ClassUnit::PRIVATE
            );

        std::string result = myClass->compile();

        QVERIFY(result.find("class MyClass")
                != std::string::npos);

        QVERIFY(result.find("public void normalMethod()")
                != std::string::npos);

        QVERIFY(result.find("public final void finalMethod()")
                != std::string::npos);

        QVERIFY(result.find("private static void printMethod()")
                != std::string::npos);

        QVERIFY(result.find("System.out.println(\"Hello Java\")")
                != std::string::npos);
    }

    void testJavaAbstract()
    {
        JAVAMethodUnit method(
            "abstractMethod",
            "void",
            JAVAMethodUnit::ABSTRACT
            );

        std::string result = method.compile();

        QVERIFY(result.find("abstract void abstractMethod();")
                != std::string::npos);
    }

    void testJavaExceptions()
    {
        JAVAMethodUnit method1(
            "badMethod1",
            "void",
            JAVAMethodUnit::ABSTRACT |
                JAVAMethodUnit::FINAL
            );

        QVERIFY_EXCEPTION_THROWN(
            method1.compile(),
            std::runtime_error
            );

        JAVAMethodUnit method2(
            "badMethod2",
            "void",
            JAVAMethodUnit::ABSTRACT |
                JAVAMethodUnit::STATIC
            );

        QVERIFY_EXCEPTION_THROWN(
            method2.compile(),
            std::runtime_error
            );
    }

    void testCSAbstractMethodBody()
    {
        CSMethodUnit method(
            "abstractMethod",
            "void",
            CSMethodUnit::ABSTRACT
            );

        method.add(
            std::make_shared<CSPrintOperatorUnit>(
                "ShouldNotAppear"
                )
            );

        std::string result = method.compile();

        QVERIFY(result.find("ShouldNotAppear")
                == std::string::npos);
    }

    void testCSSealed()
    {
        CSMethodUnit method(
            "sealedMethod",
            "void",
            CSMethodUnit::SEALED
            );

        std::string result = method.compile();

        QVERIFY(result.find("sealed void sealedMethod()")
                != std::string::npos);
    }

    void testFactories()
    {
        CppGeneratorFactory cppFactory;
        CSGeneratorFactory csFactory;
        JAVAGeneratorFactory javaFactory;

        QVERIFY(cppFactory.CreateClassUnit("A") != nullptr);
        QVERIFY(csFactory.CreateClassUnit("B") != nullptr);
        QVERIFY(javaFactory.CreateClassUnit("C") != nullptr);

        QVERIFY(cppFactory.CreateMethodUnit(
                    "f",
                    "void",
                    0
                    ) != nullptr);

        QVERIFY(csFactory.CreatePrintOperatorUnit(
                    "text"
                    ) != nullptr);

        QVERIFY(javaFactory.CreateMethodUnit(
                    "g",
                    "void",
                    0
                    ) != nullptr);
    }

    void testNestedCompile()
    {
        CppGeneratorFactory factory;

        auto method =
            factory.CreateMethodUnit(
                "nested",
                "void",
                0
                );

        method->add(
            factory.CreatePrintOperatorUnit(
                "NestedText"
                )
            );

        std::string result = method->compile();

        QVERIFY(result.find("printf( \"NestedText\" );")
                != std::string::npos);
    }
};

QTEST_APPLESS_MAIN(GeneratorTests)

#include "main.moc"
