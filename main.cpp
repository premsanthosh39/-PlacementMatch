#include "models/student.h"
#include "models/company.h"
#include "services/search.h"
#include "services/registration.h"
#include "services/companyregistration.h"
#include "services/eligibilitychecker.h"
#include "services/csvstorage.h"
#include "services/applicationsystem.h"
#include "utils/trie.h"
#include "strategies/eligibilitystrategy.h"
#include "utils/logger.h"
#include "utils/config.h" 
#include <iostream>
#include <limits>
#include <unordered_map>
#include <queue>
#include <utility>
#include <algorithm>

void findCompaniesWithMinPackage(std::vector<Company>& companies, double minPackage) {
    std::sort(companies.begin(), companies.end(),
        [](const Company& a, const Company& b) {
            return a.get_Packages() < b.get_Packages();
        });

    auto it = std::lower_bound(companies.begin(), companies.end(), minPackage,
        [](const Company& c, double value) {
            return c.get_Packages() < value;
        });

    std::cout << "\nCompanies with package >= " << minPackage << " LPA:\n";
    if (it == companies.end()) {
        std::cout << "None found.\n";
        return;
    }
    for (auto iter = it; iter != companies.end(); ++iter) {
        iter->display();
    }
}

Student* findStudentByRoll(std::unordered_map<std::string, Student*>& index, const std::string& rollNo) {
    auto it = index.find(rollNo);
    if (it == index.end()) return nullptr;
    return it->second;
}

Company* findCompanyByName(std::unordered_map<std::string, Company*>& index, const std::string& name) {
    auto it = index.find(name);
    if (it == index.end()) return nullptr;
    return it->second;
}

void updateStudent(std::vector<Student>& students, const std::string& rollNo) {
    for (auto& s : students) {
        if (s.get_Roll_No() == rollNo) {
            double newCgpa; int newBacklogs; int newYear;
            std::cout << "Enter new CGPA: "; std::cin >> newCgpa;
            std::cout << "Enter new Backlogs: "; std::cin >> newBacklogs;
            std::cout << "Enter new Graduation Year: "; std::cin >> newYear;
            s.set_Cgpa(newCgpa);
            s.set_Backlogs(newBacklogs);
            s.set_Graduation_Year(newYear);
            std::cout << "Student updated.\n";
            logevent("Student updated: " + rollNo);
            return;
        }
    }
    std::cout << "Student not found.\n";
}

void deleteStudent(std::vector<Student>& students, const std::string& rollNo) {
    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->get_Roll_No() == rollNo) {
            students.erase(it);
            std::cout << "Student deleted.\n";
            logevent("Student deleted: " + rollNo);
            return;
        }
    }
    std::cout << "Student not found.\n";
}

void updateCompany(std::vector<Company>& companies, const std::string& name) {
    for (auto& c : companies) {
        if (c.get_Company_Name() == name) {
            double newCgpa, newPackage; int newBacklogs, newYear;
            std::cout << "Enter new Min CGPA: "; std::cin >> newCgpa;
            std::cout << "Enter new Max Backlogs: "; std::cin >> newBacklogs;
            std::cout << "Enter new Package: "; std::cin >> newPackage;
            std::cout << "Enter new Eligible Graduation Year: "; std::cin >> newYear;
            c.set_Cgpa(newCgpa);
            c.set_max_Backlogs(newBacklogs);
            c.set_Packages(newPackage);
            c.set_Eligible_Graduation_Year(newYear);
            std::cout << "Company updated.\n";
            logevent("Company updated: " + name);
            return;
        }
    }
    std::cout << "Company not found.\n";
}

void deleteCompany(std::vector<Company>& companies, const std::string& name) {
    for (auto it = companies.begin(); it != companies.end(); ++it) {
        if (it->get_Company_Name() == name) {
            companies.erase(it);
            std::cout << "Company deleted.\n";
            logevent("Company deleted: " + name);
            return;
        }
    }
    std::cout << "Company not found.\n";
}

void showEligibleCompaniesRanked(std::vector<Company>& companies, Student& student) {
    std::priority_queue<std::pair<double,std::string>> pq;
    for(auto& c : companies){
        eligibilityresult r = eligibilitychecker(student,c);
        if(r.eligible){
            pq.push({c.get_Packages(),c.get_Company_Name()});
        }
    }
    if(pq.empty()){
        std::cout<<"No eligible companies for "<<student.get_Name()<<std::endl;
        return;
    }
    std::cout << "\nEligible companies for " << student.get_Name() << " (highest package first):\n";
    while (!pq.empty()) {
        auto top = pq.top();
        std::cout << top.second << " - " << top.first << " LPA\n";
        pq.pop();
    }
}

int main() {
    Config config;
    config.load("config/config.txt");

    std::string studentsFile = config.get("students_file", "data/students.csv");
    std::string companiesFile = config.get("companies_file", "data/companies.csv");
    std::string applicationsFile = config.get("applications_file", "data/applications.csv");

    std::vector<Student> students = loadStudents(studentsFile);
    std::vector<Company> companies = loadCompanies(companiesFile);
    std::vector<Application> applications = loadApplications(applicationsFile);

    std::unordered_map<std::string, Student*> studentIndex;
    for (auto& s : students) studentIndex[s.get_Roll_No()] = &s;

    std::unordered_map<std::string, Company*> companyIndex;
    for (auto& c : companies) companyIndex[c.get_Company_Name()] = &c;

    Trie studentNameTrie;
    for (const auto& s : students) studentNameTrie.insert(s.get_Name());

    while (true) {
        std::cout << "\n===== Placement Eligibility Checker =====\n";
        std::cout << "1. Register Student\n";
        std::cout << "2. Register Company\n";
        std::cout << "3. Check Eligibility\n";
        std::cout << "4. View All Students\n";
        std::cout << "5. View All Companies\n";
        std::cout << "6. Search Student (substring)\n";
        std::cout << "7. Search Company (substring)\n";
        std::cout << "8. View Companies Sorted by Package\n";
        std::cout << "9. Apply to Company\n";
        std::cout << "10. View My Applications\n";
        std::cout << "11. Search Student by Name Prefix (Trie)\n";
        std::cout << "12. Update Student\n";
        std::cout << "13. Delete Student\n";
        std::cout << "14. Update Company\n";
        std::cout << "15. Delete Company\n";
        std::cout << "16. Update Application Status\n";
        std::cout << "17. Delete/Withdraw Application\n";
        std::cout << "18. Eligible Companies for a Student (Ranked)\n";
        std::cout << "19. Companies with Minimum Package (Binary Search)\n";
        std::cout << "20. Exit\n";
        std::cout << "Enter choice: ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: {
                registerstudents(students);
                saveStudents(students, studentsFile);
                studentIndex.clear();
                for (auto& s : students) studentIndex[s.get_Roll_No()] = &s;
                studentNameTrie.insert(students.back().get_Name());
                logevent("Student registered: " + students.back().get_Roll_No());
                break;
            }
            case 2: {
                registercompanies(companies);
                saveCompanies(companies, companiesFile);
                companyIndex.clear();
                for (auto& c : companies) companyIndex[c.get_Company_Name()] = &c;
                logevent("Company registered: " + companies.back().get_Company_Name());
                break;
            }
            case 3: {
                std::string rollNo, companyName;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter Roll Number: ";
                std::getline(std::cin, rollNo);
                std::cout << "Enter Company Name: ";
                std::getline(std::cin, companyName);

                Student* s = findStudentByRoll(studentIndex, rollNo);
                Company* c = findCompanyByName(companyIndex, companyName);
                if (!s) { std::cout << "Student not found.\n"; break; }
                if (!c) { std::cout << "Company not found.\n"; break; }

                std::cout << "Use (1) Standard or (2) Strict eligibility rules? ";
                int ruleChoice;
                std::cin >> ruleChoice;
                std::string strategyType = (ruleChoice == 2) ? "strict" : "standard";

                EligibilityStrategy* strategy = EligibilityStrategyFactory::create(strategyType);
                eligibilityresult r = strategy->evaluate(*s, *c);
                delete strategy;

                if (r.eligible) std::cout << s->get_Name() << " is ELIGIBLE for " << c->get_Company_Name() << "!\n";
                else std::cout << s->get_Name() << " is NOT eligible: " << r.result << "\n";
                break;
            }
            case 4:
                for (const auto& s : students) s.display();
                break;
            case 5:
                for (const auto& c : companies) c.display();
                break;
            case 6: {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::string query;
                std::cout << "Enter student name to search: ";
                std::getline(std::cin, query);
                searchStudentByName(students, query);
                break;
            }
            case 7: {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::string query;
                std::cout << "Enter company name to search: ";
                std::getline(std::cin, query);
                searchCompanyByName(companies, query);
                break;
            }
            case 8: {
                std::vector<Company> sortedCompanies = getCompaniesSortedByPackage(companies);
                std::cout << "\n--- Companies sorted by package (highest first) ---\n";
                for (const auto& c : sortedCompanies) c.display();
                break;
            }
            case 9: {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::string rollNo, companyName;
                std::cout << "Enter your Roll Number: ";
                std::getline(std::cin, rollNo);
                std::cout << "Enter Company Name to apply to: ";
                std::getline(std::cin, companyName);
                bool success = applytocompany(applications, students, companies, rollNo, companyName);
                saveApplications(applications, applicationsFile);
                if (success) logevent("Application submitted: " + rollNo + " -> " + companyName);
                break;
            }
            case 10: {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::string rollNo;
                std::cout << "Enter Roll Number: ";
                std::getline(std::cin, rollNo);
                viewapplicationforstudents(applications, rollNo);
                break;
            }
            case 11: {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::string prefix;
                std::cout << "Enter name prefix: ";
                std::getline(std::cin, prefix);
                auto matches = studentNameTrie.searchbyprefix(prefix);
                if (matches.empty()) std::cout << "No matches.\n";
                for (const auto& name : matches) std::cout << name << "\n";
                break;
            }
            case 12: {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::string rollNo;
                std::cout << "Enter Roll Number to update: ";
                std::getline(std::cin, rollNo);
                updateStudent(students, rollNo);
                saveStudents(students, studentsFile);
                studentIndex.clear();
                for (auto& s : students) studentIndex[s.get_Roll_No()] = &s;
                break;
            }
            case 13: {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::string rollNo;
                std::cout << "Enter Roll Number to delete: ";
                std::getline(std::cin, rollNo);
                deleteStudent(students, rollNo);
                saveStudents(students, studentsFile);
                studentIndex.clear();
                for (auto& s : students) studentIndex[s.get_Roll_No()] = &s;
                break;
            }
            case 14: {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::string name;
                std::cout << "Enter Company Name to update: ";
                std::getline(std::cin, name);
                updateCompany(companies, name);
                saveCompanies(companies, companiesFile);
                companyIndex.clear();
                for (auto& c : companies) companyIndex[c.get_Company_Name()] = &c;
                break;
            }
            case 15: {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::string name;
                std::cout << "Enter Company Name to delete: ";
                std::getline(std::cin, name);
                deleteCompany(companies, name);
                saveCompanies(companies, companiesFile);
                companyIndex.clear();
                for (auto& c : companies) companyIndex[c.get_Company_Name()] = &c;
                break;
            }
            case 16: {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::string rollNo, companyName, status;
                std::cout << "Enter Roll Number: ";
                std::getline(std::cin, rollNo);
                std::cout << "Enter Company Name: ";
                std::getline(std::cin, companyName);
                std::cout << "Enter new status (Applied/Shortlisted/Rejected/Selected): ";
                std::getline(std::cin, status);
                updateApplicationStatus(applications, rollNo, companyName, status);
                saveApplications(applications, applicationsFile);
                logevent("Application status updated: " + rollNo + " -> " + companyName + " : " + status);
                break;
            }
            case 17: {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::string rollNo, companyName;
                std::cout << "Enter Roll Number: ";
                std::getline(std::cin, rollNo);
                std::cout << "Enter Company Name: ";
                std::getline(std::cin, companyName);
                deleteApplication(applications, rollNo, companyName);
                saveApplications(applications, applicationsFile);
                break;
            }
            case 18: {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::string rollNo;
                std::cout << "Enter Roll Number: ";
                std::getline(std::cin, rollNo);
                Student* s = findStudentByRoll(studentIndex, rollNo);
                if (!s) { std::cout << "Student not found.\n"; break; }
                showEligibleCompaniesRanked(companies, *s);
                break;
            }
            case 19: {
                double minPkg;
                std::cout << "Enter minimum package (LPA): ";
                std::cin >> minPkg;
                findCompaniesWithMinPackage(companies, minPkg);
                break;
            }
            case 20:
                std::cout << "Exiting. Goodbye!\n";
                return 0;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}