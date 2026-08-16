#include "strategies/eligibilitystrategy.h"

eligibilityresult StandardStrategy::evaluate(const Student& student, const Company& company) const {
    return eligibilitychecker(student, company);
}

eligibilityresult StrictStrategy::evaluate(const Student& student, const Company& company) const {
    eligibilityresult base = eligibilitychecker(student, company);
    if (!base.eligible) return base;

    if (student.get_Backlogs() > 0) {
        return { false, "Strict mode: zero backlogs required" };
    }
    return { true, "" };
}

EligibilityStrategy* EligibilityStrategyFactory::create(const std::string& type) {
    if (type == "standard") {
        return new StandardStrategy();
    } else if (type == "strict") {
        return new StrictStrategy();
    }
    return nullptr;
}