#include "student.h"
#include "company.h"
#include<iostream>
#include<vector>

int main() {
    // Create a couple of students
    Student s1("21CS001", "Rahul Sharma", 8.5, "CSE", 0, {"C++", "DSA", "SQL"});
    Student s2("21EC005", "Priya Nair", 6.8, "ECE", 1, {"Python", "Verilog"});

    // Create a couple of companies
    Company c1("TI", 7.5, 0, {"CSE", "ECE"}, 24, "SDE");
    Company c2("Infosys", 6.0, 2, {"CSE", "ECE", "MECH"}, 6.5, "Analyst");

    std::cout << "===== Students =====\n";
    s1.display();
    s2.display();

    std::cout << "\n===== Companies =====\n";
    c1.display();
    c2.display();

    // Test isBranchEligible
    std::cout << "\n===== Branch Check =====\n";
    std::cout << "TI eligible for CSE? " << (c1.isbrancheligible("CSE") ? "Yes" : "No") << "\n";
    std::cout << "TI eligible for MECH? " << (c1.isbrancheligible("MECH") ? "Yes" : "No") << "\n";

    c1.display();

    return 0;
}