#ifndef APPLICATIONSYSTEM_H
#define APPLICATIONSYSTEM_H
#include "application.h"
#include "student.h"
#include "company.h"
#include <vector>

bool applicationexists(const std::vector<Application>& apps, const std::string& roll_no, const std::string& company_name);
bool applytocompany(std::vector<Application>& apps, std::vector<Student>& students,
std::vector<Company>& companies, const std::string& roll_no, const std::string& company_name);
void viewapplicationforstudents(const std::vector<Application>& apps, const std::string& rollNo);

#endif