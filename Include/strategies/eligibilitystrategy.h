#ifndef ELIGIBILITYSTRATEGY_H
#define ELIGIBILITYSTRATEGY_H
#include "models/student.h"
#include "models/company.h"
#include "services/eligibilitychecker.h"

class EligibilityStrategy {
public:
    virtual eligibilityresult evaluate(const Student& student, const Company& company) const = 0;
    virtual ~EligibilityStrategy() {}
};

class StandardStrategy : public EligibilityStrategy {
public:
    eligibilityresult evaluate(const Student& student, const Company& company) const override;
};

class StrictStrategy : public EligibilityStrategy {
public:
    eligibilityresult evaluate(const Student& student, const Company& company) const override;
};

class EligibilityStrategyFactory {
public:
    static EligibilityStrategy* create(const std::string& type);
};
#endif