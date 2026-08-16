#ifndef REGISTRATION_H
#define REGISTRATION_H
#include "models/student.h"
#include "models/company.h"
    bool rollnoexists(const std::vector<Student>& s,const std::string Roll_No);
    void registerstudents(std::vector<Student>& s);
#endif