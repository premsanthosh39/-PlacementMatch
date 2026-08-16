#include "models/student.h"
#include "models/company.h"
#include "models/application.h"
#include "services/eligibilitychecker.h"
#include "services/applicationsystem.h"
#include <iostream>
#include <cassert>
#include <vector>

void testFullApplicationFlow() {
    std::vector<Student> students;
    std::vector<Company> companies;
    std::vector<Application> applications;

    students.push_back(Student("21CS999", "Integration Test Student", 9.0, "CSE", 0, {"C++"}, 2026));
    companies.push_back(Company("IntegrationCo", 7.5, 0, {"CSE"}, 15, "SDE", 2026));

    // Step 1: confirm eligibility check works
    eligibilityresult r = eligibilitychecker(students[0], companies[0]);
    assert(r.eligible == true);

    // Step 2: apply
    bool applied = applytocompany(applications, students, companies, "21CS999", "IntegrationCo");
    assert(applied == true);
    assert(applications.size() == 1);

    // Step 3: confirm duplicate application is rejected
    bool duplicateApplied = applytocompany(applications, students, companies, "21CS999", "IntegrationCo");
    assert(duplicateApplied == false);
    assert(applications.size() == 1); // still just 1, duplicate wasn't added

    // Step 4: update status
    bool updated = updateApplicationStatus(applications, "21CS999", "IntegrationCo", "Selected");
    assert(updated == true);
    assert(applications[0].get_status() == "Selected");

    // Step 5: withdraw/delete
    bool deleted = deleteApplication(applications, "21CS999", "IntegrationCo");
    assert(deleted == true);
    assert(applications.empty());

    std::cout << "[PASS] testFullApplicationFlow\n";
}

void testIneligibleStudentCannotApply() {
    std::vector<Student> students;
    std::vector<Company> companies;
    std::vector<Application> applications;

    students.push_back(Student("21CS998", "Low CGPA Applicant", 5.0, "CSE", 0, {"C++"}, 2026));
    companies.push_back(Company("StrictCo", 8.0, 0, {"CSE"}, 25, "SDE", 2026));

    bool applied = applytocompany(applications, students, companies, "21CS998", "StrictCo");
    assert(applied == false);
    assert(applications.empty());

    std::cout << "[PASS] testIneligibleStudentCannotApply\n";
}

int main() {
    std::cout << "=== RUNNING INTEGRATION TESTS ===\n";
    testFullApplicationFlow();
    testIneligibleStudentCannotApply();
    std::cout << "=== ALL INTEGRATION TESTS PASSED ===\n";
    return 0;
}