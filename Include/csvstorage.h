#ifndef CSVSTORAGE_H
#define CSVSTORAGE_H
#include "student.h"
#include "company.h"
#include <vector>
#include <string>
#include "application.h"

std::vector<Application> loadApplications(const std::string& filename);
void saveApplications(const std::vector<Application>& apps, const std::string& filename);

std::vector<Student> loadStudents(const std::string& filename);
void saveStudents(const std::vector<Student>& students, const std::string& filename);

std::vector<Company> loadCompanies(const std::string& filename);
void saveCompanies(const std::vector<Company>& companies, const std::string& filename);

#endif