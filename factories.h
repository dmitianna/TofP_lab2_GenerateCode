#ifndef FACTORIES_H
#define FACTORIES_H

#include <memory>

#include "CPPprintoperatorUnit.h"
#include "CPPmethodunit.h"
#include "CPPclassunit.h"

#include "CSprintoperatorunit.h"
#include "CSmethodunit.h"
#include "CSclassunit.h"

#include "JAVAprintoperatorunit.h"
#include "JAVAmethodunit.h"
#include "JAVAclassunit.h"
class AbstractFactory {
public:
    virtual ~AbstractFactory() = default;
    virtual std::shared_ptr<ClassUnit> CreateClassUnit(const std::string& name, Unit::Flags flags = 0) = 0;
    virtual std::shared_ptr<MethodUnit> CreateMethodUnit(const std::string& name, const std::string& returnType, Unit::Flags flags) = 0;
    virtual std::shared_ptr<PrintOperatorUnit> CreatePrintOperatorUnit(const std::string& text) = 0;
};

class CppGeneratorFactory : public AbstractFactory {
public:
    std::shared_ptr<ClassUnit> CreateClassUnit(const std::string& name, Unit::Flags flags = 0) override {
        return std::make_shared<CPPClassUnit>(name,flags);
    }
    std::shared_ptr<MethodUnit> CreateMethodUnit(const std::string& name, const std::string& returnType, Unit::Flags flags) override {
        return std::make_shared<CPPMethodUnit>(name, returnType, flags);
    }
    std::shared_ptr<PrintOperatorUnit> CreatePrintOperatorUnit(const std::string& text) override {
        return std::make_shared<CPPPrintOperatorUnit>(text);
    }
};

class CSGeneratorFactory : public AbstractFactory {
public:
    std::shared_ptr<ClassUnit> CreateClassUnit(const std::string& name, Unit::Flags flags = 0) override {
        return std::make_shared<CSClassUnit>(name,flags);
    }
    std::shared_ptr<MethodUnit> CreateMethodUnit(const std::string& name, const std::string& returnType, Unit::Flags flags) override {
        return std::make_shared<CSMethodUnit>(name, returnType, flags);
    }
    std::shared_ptr<PrintOperatorUnit> CreatePrintOperatorUnit(const std::string& text) override {
        return std::make_shared<CSPrintOperatorUnit>(text);
    }
};

class JAVAGeneratorFactory : public AbstractFactory {
public:
    std::shared_ptr<ClassUnit> CreateClassUnit(const std::string& name, Unit::Flags flags = 0) override {
        return std::make_shared<JAVAClassUnit>(name,flags);
    }

    std::shared_ptr<MethodUnit> CreateMethodUnit(const std::string& name,const std::string& returnType,Unit::Flags flags) override {
        return std::make_shared<JAVAMethodUnit>(name,returnType,flags);
    }

    std::shared_ptr<PrintOperatorUnit> CreatePrintOperatorUnit(const std::string& text) override {
        return std::make_shared<JAVAPrintOperatorUnit>(text);
    }
};
#endif // FACTORIES_H
