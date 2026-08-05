#ifndef APPLICATION_SYSTEM_H
#define APPLICATION_SYSTEM_H
#include "application.h"
#include "student.h"
#include "company.h"
bool applicationexists(const std::vector<Application>& applications,const std::string& roll_no,const std::string& company_name);
bool applytocompany(std::vector<Application>& applications,std::vector<Student>& students,std::vector<Company>& companies,const std::string& roll_no,const std::string& company_name);
void viewapplicationforstudents(const std::vector<Application>& applications,const std::string& roll_no);
#endif