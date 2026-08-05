#include "applicationsystem.h"
#include "registration.h"
#include "companyregistration.h"
#include <iostream>

int main() {
    std::vector<Student> students;
    std::vector<Company> companies;
    std::vector<Application> applications;

    registerstudents(students);
    registercompanies(companies);

    applytocompany(applications, students, companies,
                    students[0].get_Roll_No(), companies[0].get_Company_Name());

    viewapplicationforstudents(applications, students[0].get_Roll_No());
    return 0;
}