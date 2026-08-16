#include "models/student.h"
#include "models/company.h"
#include "services/eligibilitychecker.h"
#include <iostream>
#include <cassert>

void testEligibleStudent() {
    Student s("21CS001", "Test Student", 8.5, "CSE", 0, {"C++"}, 2026);
    Company c("TestCo", 7.5, 0, {"CSE"}, 20, "SDE", 2026);
    eligibilityresult r = eligibilitychecker(s, c);
    assert(r.eligible == true);
    std::cout << "[PASS] testEligibleStudent\n";
}

void testIneligibleCGPA() {
    Student s("21CS002", "Low CGPA Student", 6.0, "CSE", 0, {"C++"}, 2026);
    Company c("TestCo", 7.5, 0, {"CSE"}, 20, "SDE", 2026);
    eligibilityresult r = eligibilitychecker(s, c);
    assert(r.eligible == false);
    std::cout << "[PASS] testIneligibleCGPA\n";
}

void testIneligibleBacklogs() {
    Student s("21CS003", "Backlog Student", 8.5, "CSE", 3, {"C++"}, 2026);
    Company c("TestCo", 7.5, 0, {"CSE"}, 20, "SDE", 2026);
    eligibilityresult r = eligibilitychecker(s, c);
    assert(r.eligible == false);
    std::cout << "[PASS] testIneligibleBacklogs\n";
}

void testIneligibleBranch() {
    Student s("21EC001", "ECE Student", 8.5, "ECE", 0, {"C++"}, 2026);
    Company c("TestCo", 7.5, 0, {"CSE"}, 20, "SDE", 2026);
    eligibilityresult r = eligibilitychecker(s, c);
    assert(r.eligible == false);
    std::cout << "[PASS] testIneligibleBranch\n";
}

void testIneligibleGradYear() {
    Student s("21CS004", "Wrong Year Student", 8.5, "CSE", 0, {"C++"}, 2027);
    Company c("TestCo", 7.5, 0, {"CSE"}, 20, "SDE", 2026);
    eligibilityresult r = eligibilitychecker(s, c);
    assert(r.eligible == false);
    std::cout << "[PASS] testIneligibleGradYear\n";
}

int main() {
    std::cout << "=== RUNNING TEST SUITE ===\n";
    testEligibleStudent();
    testIneligibleCGPA();
    testIneligibleBacklogs();
    testIneligibleBranch();
    testIneligibleGradYear();
    std::cout << "=== ALL TESTS PASSED ===\n";
    return 0;
}