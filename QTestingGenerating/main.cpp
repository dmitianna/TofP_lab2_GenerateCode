#include <QtTest>
#include "../factories.h"
std::string generateProgram(AbstractFactory& factory)
{
    auto myClass =
        factory.CreateClassUnit("MyClass");

    myClass->add(
        factory.CreateMethodUnit(
            "testFunc",
            "void",
            0
            ),
        AccessModifier::PUBLIC
        );

    return myClass->compile();
}
class GeneratorTests : public QObject
{
    Q_OBJECT

private slots:

    void testCPP()
    {
        CppGeneratorFactory factory;

        auto cls = factory.CreateClassUnit("Test");

        cls->add(
            factory.CreateMethodUnit(
                "foo",
                "void",
                MethodModifier::VIRTUAL | MethodModifier::CONST
                ),
            AccessModifier::PUBLIC
            );

        QString result =
            QString::fromStdString(cls->compile());

        QVERIFY(result.contains("virtual"));
    }

    void testCS()
    {
        CSGeneratorFactory factory;

        auto cls = factory.CreateClassUnit("Test");

        cls->add(
            factory.CreateMethodUnit(
                "foo",
                "void",
                MethodModifier::STATIC
                ),
            AccessModifier::PUBLIC
            );

        QString result =
            QString::fromStdString(cls->compile());

        QVERIFY(result.contains("static"));
    }

    void testJava()
    {
        JAVAGeneratorFactory factory;

        auto cls = factory.CreateClassUnit("Test");

        cls->add(
            factory.CreateMethodUnit(
                "foo",
                "void",
                MethodModifier::STATIC
                ),
            AccessModifier::PUBLIC
            );

        QString result =
            QString::fromStdString(cls->compile());

        QVERIFY(result.contains("static"));
    }

    void testCSConstMethod()
    {
        CSGeneratorFactory factory;

        auto cls = factory.CreateClassUnit("Test");

        cls->add(
            factory.CreateMethodUnit(
                "foo",
                "void",
                MethodModifier::CONST
                ),
            AccessModifier::PUBLIC
            );

        QVERIFY_EXCEPTION_THROWN(
            cls->compile(),
            std::runtime_error
            );
    }

    void testJavaConstMethod()
    {
        JAVAGeneratorFactory factory;

        auto cls = factory.CreateClassUnit("Test");

        cls->add(
            factory.CreateMethodUnit(
                "foo",
                "void",
                MethodModifier::CONST
                ),
            AccessModifier::PUBLIC
            );

        QVERIFY_EXCEPTION_THROWN(
            cls->compile(),
            std::runtime_error
            );
    }

    void testJavaVirtualMethod()
    {
        JAVAGeneratorFactory factory;

        auto cls = factory.CreateClassUnit("Test");

        cls->add(
            factory.CreateMethodUnit(
                "foo",
                "void",
                MethodModifier::VIRTUAL
                ),
            AccessModifier::PUBLIC
            );

        QVERIFY_EXCEPTION_THROWN(
            cls->compile(),
            std::runtime_error
            );
    }

    void testCSAbstractStaticMethod()
    {
        CSGeneratorFactory factory;

        auto cls = factory.CreateClassUnit("Test");

        cls->add(
            factory.CreateMethodUnit(
                "foo",
                "void",
                MethodModifier::ABSTRACT |
                    MethodModifier::STATIC
                ),
            AccessModifier::PUBLIC
            );

        QVERIFY_EXCEPTION_THROWN(
            cls->compile(),
            std::runtime_error
            );
    }

    void testJavaAbstractFinalMethod()
    {
        JAVAGeneratorFactory factory;

        auto cls = factory.CreateClassUnit("Test");

        cls->add(
            factory.CreateMethodUnit(
                "foo",
                "void",
                MethodModifier::ABSTRACT |
                    MethodModifier::FINAL
                ),
            AccessModifier::PUBLIC
            );

        QVERIFY_EXCEPTION_THROWN(
            cls->compile(),
            std::runtime_error
            );
    }

    void testJavaAbstractMethodInNonAbstractClass()
    {
        JAVAGeneratorFactory factory;

        auto cls = factory.CreateClassUnit("Test");

        cls->add(
            factory.CreateMethodUnit(
                "foo",
                "void",
                MethodModifier::ABSTRACT
                ),
            AccessModifier::PUBLIC
            );

        QVERIFY_EXCEPTION_THROWN(
            cls->compile(),
            std::runtime_error
            );
    }

    void testJavaAbstractClass()
    {
        JAVAGeneratorFactory factory;

        auto cls = factory.CreateClassUnit(
            "Test",
            ClassModifier::ABSTRACT_CLASS
            );

        cls->add(
            factory.CreateMethodUnit(
                "foo",
                "void",
                MethodModifier::ABSTRACT
                ),
            AccessModifier::PUBLIC
            );

        QString result =
            QString::fromStdString(cls->compile());

        QVERIFY(result.contains("abstract class"));
    }

    void testCSAbstractSealedClass()
    {
        CSGeneratorFactory factory;

        auto cls = factory.CreateClassUnit(
            "Test",
            ClassModifier::ABSTRACT_CLASS |
                ClassModifier::SEALED_CLASS
            );

        QVERIFY_EXCEPTION_THROWN(
            cls->compile(),
            std::runtime_error
            );
    }


    void testCSAbstractSealedMethod()
    {
        CSGeneratorFactory factory;

        auto cls = factory.CreateClassUnit("Test");

        cls->add(
            factory.CreateMethodUnit(
                "foo",
                "void",
                MethodModifier::ABSTRACT |
                    MethodModifier::SEALED
                ),
            AccessModifier::PUBLIC
            );

        QVERIFY_EXCEPTION_THROWN(
            cls->compile(),
            std::runtime_error
            );
    }

    void testCSVirtualStaticMethod()
    {
        CSGeneratorFactory factory;

        auto cls = factory.CreateClassUnit("Test");

        cls->add(
            factory.CreateMethodUnit(
                "foo",
                "void",
                MethodModifier::VIRTUAL |
                    MethodModifier::STATIC
                ),
            AccessModifier::PUBLIC
            );

        QVERIFY_EXCEPTION_THROWN(
            cls->compile(),
            std::runtime_error
            );
    }

    void testJavaAbstractStaticMethod()
    {
        JAVAGeneratorFactory factory;

        auto cls = factory.CreateClassUnit("Test");

        cls->add(
            factory.CreateMethodUnit(
                "foo",
                "void",
                MethodModifier::ABSTRACT |
                    MethodModifier::STATIC
                ),
            AccessModifier::PUBLIC
            );

        QVERIFY_EXCEPTION_THROWN(
            cls->compile(),
            std::runtime_error
            );
    }

    void testJavaAbstractFinalClass()
    {
        JAVAGeneratorFactory factory;

        auto cls = factory.CreateClassUnit(
            "Test",
            ClassModifier::ABSTRACT_CLASS |
                ClassModifier::FINAL_CLASS
            );

        QVERIFY_EXCEPTION_THROWN(
            cls->compile(),
            std::runtime_error
            );
    }

    void testCSAbstractMethodWithBody()
    {
        CSGeneratorFactory factory;

        auto method = factory.CreateMethodUnit(
            "foo",
            "void",
            MethodModifier::ABSTRACT
            );

        method->add(
            factory.CreatePrintOperatorUnit("Hello")
            );

        QVERIFY_EXCEPTION_THROWN(
            method->compile(),
            std::runtime_error
            );
    }
    void testCSExternMethodWithBody()
    {
        CSGeneratorFactory factory;

        auto method = factory.CreateMethodUnit(
            "foo",
            "void",
            MethodModifier::EXTERN
            );

        method->add(
            factory.CreatePrintOperatorUnit("Hello")
            );

        QVERIFY_EXCEPTION_THROWN(
            method->compile(),
            std::runtime_error
            );
    }
    void testJavaAbstractMethodWithBody()
    {
        JAVAGeneratorFactory factory;

        auto method = factory.CreateMethodUnit(
            "foo",
            "void",
            MethodModifier::ABSTRACT
            );

        method->add(
            factory.CreatePrintOperatorUnit("Hello")
            );

        QVERIFY_EXCEPTION_THROWN(
            method->compile(),
            std::runtime_error
            );
    }
    void testCSExternMethod()
    {
        CSGeneratorFactory factory;

        auto method = factory.CreateMethodUnit(
            "foo",
            "void",
            MethodModifier::EXTERN
            );

        QString result =
            QString::fromStdString(method->compile());

        QVERIFY(result.contains("extern void foo()"));
    }
    void testCSAbstractMethod()
    {
        CSGeneratorFactory factory;

        auto method = factory.CreateMethodUnit(
            "foo",
            "void",
            MethodModifier::ABSTRACT
            );

        QString result =
            QString::fromStdString(method->compile());

        QVERIFY(result.contains("abstract void foo()"));
    }
    void testJavaFinalMethod()
    {
        JAVAGeneratorFactory factory;

        auto method = factory.CreateMethodUnit(
            "foo",
            "void",
            MethodModifier::FINAL
            );

        QString result =
            QString::fromStdString(method->compile());

        QVERIFY(result.contains("final void foo()"));
    }
    void testJavaFinalClass()
    {
        JAVAGeneratorFactory factory;

        auto cls = factory.CreateClassUnit(
            "Test",
            ClassModifier::FINAL_CLASS
            );

        QString result =
            QString::fromStdString(cls->compile());

        QVERIFY(result.contains("class Test"));
    }
    void testCSAbstractClass()
    {
        CSGeneratorFactory factory;

        auto cls = factory.CreateClassUnit(
            "Test",
            ClassModifier::ABSTRACT_CLASS
            );

        auto method = factory.CreateMethodUnit(
            "foo",
            "void",
            MethodModifier::ABSTRACT
            );

        cls->add(
            method,
            AccessModifier::PUBLIC
            );

        QString result =
            QString::fromStdString(cls->compile());

        QVERIFY(result.contains("abstract class Test"));
    }
    void testCSInternalAccessModifier()
    {
        CSGeneratorFactory factory;

        auto cls = factory.CreateClassUnit("Test");

        cls->add(
            factory.CreateMethodUnit(
                "foo",
                "void",
                0
                ),
            AccessModifier::INTERNAL
            );

        QString result =
            QString::fromStdString(cls->compile());

        QVERIFY(result.contains("internal void foo()"));
    }
    void testCSProtectedInternalAccessModifier()
    {
        CSGeneratorFactory factory;

        auto cls = factory.CreateClassUnit("Test");

        cls->add(
            factory.CreateMethodUnit(
                "foo",
                "void",
                0
                ),
            AccessModifier::PROTECTED_INTERNAL
            );

        QString result =
            QString::fromStdString(cls->compile());

        QVERIFY(result.contains("protected internal void foo()"));
    }
    void testCSPrivateProtectedAccessModifier()
    {
        CSGeneratorFactory factory;

        auto cls = factory.CreateClassUnit("Test");

        cls->add(
            factory.CreateMethodUnit(
                "foo",
                "void",
                0
                ),
            AccessModifier::PRIVATE_PROTECTED
            );

        QString result =
            QString::fromStdString(cls->compile());

        QVERIFY(result.contains("private protected void foo()"));
    }

    void testCSFileAccessModifier()
    {
        CSGeneratorFactory factory;

        auto cls = factory.CreateClassUnit("Test");

        cls->add(
            factory.CreateMethodUnit(
                "foo",
                "void",
                0
                ),
            AccessModifier::FILE_ACCESS
            );

        QString result =
            QString::fromStdString(cls->compile());

        QVERIFY(result.contains("file void foo()"));
    }
    void testCPPPrintOperator()
    {
        CppGeneratorFactory factory;

        auto op =
            factory.CreatePrintOperatorUnit("Hello");

        QString result =
            QString::fromStdString(op->compile());

        QVERIFY(result.contains("printf"));
    }
    void testCSPrintOperator()
    {
        CSGeneratorFactory factory;

        auto op =
            factory.CreatePrintOperatorUnit("Hello");

        QString result =
            QString::fromStdString(op->compile());

        QVERIFY(result.contains("Console.WriteLine"));
    }
    void testJavaPrintOperator()
    {
        JAVAGeneratorFactory factory;

        auto op =
            factory.CreatePrintOperatorUnit("Hello");

        QString result =
            QString::fromStdString(op->compile());

        QVERIFY(result.contains("System.out.println"));
    }
    void testCPPStaticMethod()
    {
        CppGeneratorFactory factory;

        auto method =
            factory.CreateMethodUnit(
                "foo",
                "void",
                MethodModifier::STATIC
                );

        QString result =
            QString::fromStdString(method->compile());

        QVERIFY(result.contains("static void foo()"));
    }
    void testCPPRegularMethod()
    {
        CppGeneratorFactory factory;

        auto method =
            factory.CreateMethodUnit(
                "foo",
                "void",
                0
                );

        QString result =
            QString::fromStdString(method->compile());

        QVERIFY(result.contains("void foo()"));
        QVERIFY(!result.contains("static"));
        QVERIFY(!result.contains("virtual"));
    }
    void testJavaRegularMethod()
    {
        JAVAGeneratorFactory factory;

        auto method =
            factory.CreateMethodUnit(
                "foo",
                "void",
                0
                );

        QString result =
            QString::fromStdString(method->compile());

        QVERIFY(result.contains("void foo()"));
        QVERIFY(!result.contains("abstract"));
        QVERIFY(!result.contains("final"));
        QVERIFY(!result.contains("static"));
    }
    void testCSVirtualMethod()
    {
        CSGeneratorFactory factory;

        auto method =
            factory.CreateMethodUnit(
                "foo",
                "void",
                MethodModifier::VIRTUAL
                );

        QString result =
            QString::fromStdString(method->compile());

        QVERIFY(result.contains("virtual void foo()"));
    }
    void testCSSealedMethod()
    {
        CSGeneratorFactory factory;

        auto method =
            factory.CreateMethodUnit(
                "foo",
                "void",
                MethodModifier::SEALED
                );

        QString result =
            QString::fromStdString(method->compile());

        QVERIFY(result.contains("sealed void foo()"));
    }
    void testGenerateProgramCPP()
    {
        CppGeneratorFactory factory;

        QString result =
            QString::fromStdString(generateProgram(factory));

        QVERIFY(result.contains("class MyClass"));
        QVERIFY(result.contains("void testFunc()"));
    }

    void testGenerateProgramCS()
    {
        CSGeneratorFactory factory;

        QString result =
            QString::fromStdString(generateProgram(factory));

        QVERIFY(result.contains("class MyClass"));
        QVERIFY(result.contains("void testFunc()"));
    }

    void testGenerateProgramJava()
    {
        JAVAGeneratorFactory factory;

        QString result =
            QString::fromStdString(generateProgram(factory));

        QVERIFY(result.contains("class MyClass"));
        QVERIFY(result.contains("void testFunc()"));
    }
    void testCPPMethodWithBody()
    {
        CppGeneratorFactory factory;

        auto method =
            factory.CreateMethodUnit(
                "foo",
                "void",
                0
                );

        method->add(
            factory.CreatePrintOperatorUnit("Hello")
            );

        QString result =
            QString::fromStdString(method->compile());

        QVERIFY(result.contains("printf"));
    }
    void testJavaMethodWithBody()
    {
        JAVAGeneratorFactory factory;

        auto method =
            factory.CreateMethodUnit(
                "foo",
                "void",
                0
                );

        method->add(
            factory.CreatePrintOperatorUnit("Hello")
            );

        QString result =
            QString::fromStdString(method->compile());

        QVERIFY(result.contains("System.out.println"));
    }
};

QTEST_APPLESS_MAIN(GeneratorTests)

#include "main.moc"
