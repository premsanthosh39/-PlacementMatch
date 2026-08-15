#include "search.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <vector>
#include "student.h"
#include "company.h"

std::string toLower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}

void searchStudentByName(const std::vector<Student>& students, const std::string& query) {
    std::string lowerQuery = toLower(query);
    bool found = false;
    for (const auto& s : students) {
        if (toLower(s.get_Name()).find(lowerQuery) != std::string::npos) {
            s.display();
            found = true;
        }
    }
    if (!found) std::cout << "No matching student found.\n";
}

void searchCompanyByName(const std::vector<Company>& companies, const std::string& query) {
    std::string lowerQuery = toLower(query);
    bool found = false;
    for (const auto& c : companies) {
        if (toLower(c.get_Company_Name()).find(lowerQuery) != std::string::npos) {
            c.display();
            found = true;
        }
    }
    if (!found) std::cout << "No matching company found.\n"; 
}
std::vector<Company> getCompaniesSortedByPackage(const std::vector<Company>& companies) {
    std::vector<Company> sorted = companies;
    std::sort(sorted.begin(), sorted.end(),
        [](const Company& a, const Company& b) {
            return a.get_Packages() > b.get_Packages();
        });
    return sorted;
}