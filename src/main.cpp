#include "eligibilitychecker.h"
#include <iostream>

int main() {
    Student s1("21CS001", "Rahul Sharma", 8.5, "CSE", 0, {"C++", "DSA", "SQL"});
    Student s2("21ME011", "Vivek Iyer", 5.9, "MECH", 3, {"MATLAB"});
    Company c("TI", 7.5, 0, {"CSE", "ECE"}, 24, "SDE");

    auto r1 = eligibilitychecker(s1, c);
    auto r2 = eligibilitychecker(s2, c);

    std::cout << "s1 eligible: " << " reason: " << r1.result << "\n";
    std::cout << "s2 eligible: " << " reason: " << r2.result << "\n";

    return 0;
}