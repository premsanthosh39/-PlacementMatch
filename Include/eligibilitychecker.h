#ifndef ELIGIBILITYCHECKER_H
#define ELIGIBILITYCHECKER_H
#include "student.h"
#include "company.h"
#include<string>
struct eligibilityresult{
    bool eligible;
    std::string result;
};
eligibilityresult eligibilitychecker(const Student& student,const Company& company);
#endif