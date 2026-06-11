#include <QtTest>
#include "../factories.h"

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
};

QTEST_APPLESS_MAIN(GeneratorTests)

#include "main.moc"
