#include "registration.h"
#include <iostream>

int main() {
    std::vector<Student> students;

    registerstudents(students);   
    registerstudents(students);    

    std::cout << "\n--- Current students ---\n";
    for (const auto& s : students) s.display();

    return 0;
}