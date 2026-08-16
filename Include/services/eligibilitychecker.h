#ifndef ELIGIBILITYCHECKER_H
#define ELIGIBILITYCHECKER_H
#include "models/student.h"
#include "models/company.h"
#include<string>
struct eligibilityresult{
    bool eligible;
    std::string result;
};
eligibilityresult eligibilitychecker(const Student& student,const Company& company);
#endif