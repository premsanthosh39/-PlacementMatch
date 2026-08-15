#include "registration.h"
#include<iostream>
#include<limits> 
bool rollnoexists(const std::vector<Student>& students,const std::string Roll_No){
    for(auto& s:students){
        if(s.get_Roll_No() == Roll_No) return true;
    }
    return false;
}
void registerstudents(std::vector<Student>& students){
    std::string name,rollno,branch;
    int backlogs;
    double cgpa;
    std::vector<std::string> skills;

    std::cout<<"Enter your roll number : ";
    std::cin>>rollno;
    if(rollnoexists(students,rollno)){
        std::cout<<"You are already registered\n";
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout<<"Enter your name : ";
    getline(std::cin,name);

    while(true){
        std::cout << "Enter CGPA (0-10): ";
        if (!(std::cin >> cgpa) || cgpa < 0 || cgpa > 10) {
            std::cout << "Invalid CGPA. Try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else break;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter Branch: ";
    std::getline(std::cin, branch);

    while (true) {
        std::cout << "Enter Backlogs: ";
        if (!(std::cin >> backlogs) || backlogs < 0) {
            std::cout << "Invalid backlog count. Try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else break;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter Skills (comma-separated, e.g. C++,DSA,SQL): ";
    std::string skillsLine;
    std::getline(std::cin, skillsLine);

    int gradYear;
    while (true) {
        std::cout << "Enter Graduation Year (e.g. 2026): ";
        if (!(std::cin >> gradYear) || gradYear < 2000 || gradYear > 2100) {
            std::cout << "Invalid year. Try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else break;
    }
    std::string current;
    for (char c : skillsLine) {
        if (c == ',') { 
            skills.push_back(current); 
            current.clear(); 
        }
        else current += c;
    }
    if (!current.empty()) skills.push_back(current);

    students.push_back(Student(rollno, name, cgpa, branch, backlogs, skills,gradYear));
    std::cout << "Student registered successfully.\n";
}