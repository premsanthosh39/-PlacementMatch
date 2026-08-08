#include "student.h"
#include "company.h"
#include "search.h"
#include "registration.h"
#include "companyregistration.h"
#include "eligibilitychecker.h"
#include "csvstorage.h"
#include "applicationsystem.h"
#include <iostream>
#include <limits>

Student* findStudentByRoll(std::vector<Student>& students, const std::string& rollNo) {
    for (auto& s : students) {
        if (s.get_Roll_No() == rollNo) return &s;
    }
    return nullptr;
}

Company* findCompanyByName(std::vector<Company>& companies, const std::string& name) {
    for (auto& c : companies) {
        if (c.get_Company_Name() == name) return &c;
    }
    return nullptr;
}

int main() {
    std::vector<Student> students = loadStudents("data/students.csv");
    std::vector<Company> companies = loadCompanies("data/companies.csv");
    std::vector<Application> applications = loadApplications("data/applications.csv");

    while (true) {
        std::cout << "\n===== Placement Eligibility Checker =====\n";
        std::cout << "1. Register Student\n";
        std::cout << "2. Register Company\n";
        std::cout << "3. Check Eligibility\n";
        std::cout << "4. View All Students\n";
        std::cout << "5. View All Companies\n";
        std::cout << "6. Search Student\n";
        std::cout << "7. Search Company\n";
        std::cout << "8. View Companies Sorted by Package\n";
        std::cout << "9. Apply to Company\n";
        std::cout << "10. View My Applications\n";
        std::cout << "11. Exit\n";
        std::cout << "Enter choice: ";
        int choice;
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                registerstudents(students);
                saveStudents(students, "data/students.csv");
                break;

            case 2:
                registercompanies(companies);
                saveCompanies(companies, "data/companies.csv");
                break;

            case 3: {
                std::string rollNo, companyName;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter Roll Number: ";
                std::getline(std::cin, rollNo);
                std::cout << "Enter Company Name: ";
                std::getline(std::cin, companyName);

                Student* s = findStudentByRoll(students, rollNo);
                Company* c = findCompanyByName(companies, companyName);

                if (!s) { std::cout << "Student not found.\n"; break; }
                if (!c) { std::cout << "Company not found.\n"; break; }

                eligibilityresult r = eligibilitychecker(*s, *c);
                if (r.eligible) {
                    std::cout << s->get_Name() << " is ELIGIBLE for " << c->get_Company_Name() << "!\n";
                } else {
                    std::cout << s->get_Name() << " is NOT eligible: " << r.result << "\n";
                }
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

                applytocompany(applications, students, companies, rollNo, companyName);
                saveApplications(applications, "data/applications.csv");
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

            case 11:
                std::cout << "Exiting. Goodbye!\n";
                return 0;

            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}