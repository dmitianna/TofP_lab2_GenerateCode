#ifndef FACTORIES_H
#define FACTORIES_H

#include <memory>

#include "CPPprintOperatorUnit.h"
#include "CPPmethodUnit.h"
#include "CPPclassUnit.h"

#include "CSprintOperatorUnit.h"
#include "CSmethodUnit.h"
#include "CSclassUnit.h"

#include "JAVAprintOperatorUnit.h"
#include "JAVAmethodUnit.h"
#include "JAVAclassUnit.h"
class AbstractFactory {
public:
    virtual ~AbstractFactory() = default;
    virtual std::shared_ptr<ClassUnit> CreateClassUnit(const std::string& name) = 0;
    virtual std::shared_ptr<MethodUnit> CreateMethodUnit(const std::string& name, const std::string& returnType, Unit::Flags flags) = 0;
    virtual std::shared_ptr<PrintOperatorUnit> CreatePrintOperatorUnit(const std::string& text) = 0;
};

class CppGeneratorFactory : public AbstractFactory {
public:
    std::shared_ptr<ClassUnit> CreateClassUnit(const std::string& name) override {
        return std::make_shared<CPPClassUnit>(name);
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
    std::shared_ptr<ClassUnit> CreateClassUnit(const std::string& name) override {
        return std::make_shared<CSClassUnit>(name);
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
    std::shared_ptr<ClassUnit> CreateClassUnit(const std::string& name) override {
        return std::make_shared<JAVAClassUnit>(name);
    }

    std::shared_ptr<MethodUnit> CreateMethodUnit(const std::string& name,const std::string& returnType,Unit::Flags flags) override {
        return std::make_shared<JAVAMethodUnit>(name,returnType,flags);
    }

    std::shared_ptr<PrintOperatorUnit> CreatePrintOperatorUnit(const std::string& text) override {
        return std::make_shared<JAVAPrintOperatorUnit>(text);
    }
};
#endif // FACTORIES_H
