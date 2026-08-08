#ifndef SEARCH_H
#define SEARCH_H
#include "student.h"
#include "company.h"
#include <vector>
#include <string>

std::string toLower(std::string s);
void searchStudentByName(const std::vector<Student>& students, const std::string& query);
void searchCompanyByName(const std::vector<Company>& companies, const std::string& query);
std::vector<Company> getCompaniesSortedByPackage(const std::vector<Company>& companies);

#endif