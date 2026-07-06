#include <iostream>
#include <vector>
#include <fstream>
#include "student.h"
#include "company.h"
using namespace std;

vector<Student> students;
vector<Company> companies;

//SAVE AND LOAD 
void saveStudents() {
    ofstream f("students.txt");
    for (auto& s : students) {
        f << s.Name << "\n" << s.Roll_No << "\n"
          << s.Cgpa << "\n" << s.Twelth << "\n"
          << s.Tenth << "\n" << s.Backlogs << "\n";
    }
    f.close();
}

void loadStudents() {
    ifstream f("students.txt");
    if (!f) return;
    Student s;
    while (getline(f, s.Name)) {
        f >> s.Roll_No >> s.Cgpa >> s.Twelth >> s.Tenth >> s.Backlogs;
        f.ignore();
        students.push_back(s);
    }
    f.close();
}

void saveCompanies() {
    ofstream f("companies.txt");
    for (auto& c : companies) {
        f << c.Name << "\n" << c.Mincgpa << "\n"
          << c.Mintwelth << "\n" << c.Mintenth << "\n"
          << c.Maxbacklogs << "\n";
    }
    f.close();
}

void loadCompanies() {
    ifstream f("companies.txt");
    if (!f) return;
    Company c;
    while (getline(f, c.Name)) {
        f >> c.Mincgpa >> c.Mintwelth >> c.Mintenth >> c.Maxbacklogs;
        f.ignore();
        companies.push_back(c);
    }
    f.close();
}

//STUDENT FUNCTIONS  
void addStudent() {
    Student s;
    s.input();
    students.push_back(s);
    saveStudents();
    cout << "Student added successfully!" << endl;
}

void viewStudents() {
    if (students.empty()) {
        cout << "No students found." << endl;
        return;
    }
    for (auto& s : students) s.display();
}

void searchStudent() {
    int roll;
    cout << "Enter Roll Number to search: ";
    cin >> roll;
    for (auto& s : students) {
        if (s.Roll_No == roll) {
            s.display();
            return;
        }
    }
    cout << "Student not found." << endl;
}

void deleteStudent() {
    int roll;
    cout << "Enter Roll Number to delete: ";
    cin >> roll;
    for (int i = 0; i < students.size(); i++) {
        if (students[i].Roll_No == roll) {
            students.erase(students.begin() + i);
            saveStudents();
            cout << "Student deleted." << endl;
            return;
        }
    }
    cout << "Student not found." << endl;
}

//COMPANY FUNCTIONS 
void addCompany() {
    Company c;
    c.input();
    companies.push_back(c);
    saveCompanies();
    cout << "Company added successfully!" << endl;
}

void viewCompanies() {
    if (companies.empty()) {
        cout << "No companies found." << endl;
        return;
    }
    for (auto& c : companies) c.display();
}

void deleteCompany() {
    string cname;
    cout << "Enter Company Name to delete: ";
    cin.ignore();
    getline(cin, cname);
    for (int i = 0; i < companies.size(); i++) {
        if (companies[i].Name == cname) {
            companies.erase(companies.begin() + i);
            saveCompanies();
            cout << "Company deleted." << endl;
            return;
        }
    }
    cout << "Company not found." << endl;
}

//ELIGIBILITY CHECK 
void checkEligibility() {
    int roll;
    cout << "Enter Student Roll Number: ";
    cin >> roll;

    Student* found = nullptr;
    for (auto& s : students) {
        if (s.Roll_No == roll) {
            found = &s;
            break;
        }
    }

    if (!found) {
        cout << "Student not found." << endl;
        return;
    }

    cout << "\n=== Eligibility Report for " << found->Name << " ===" << endl;

    bool anyEligible = false;

    for (auto& c : companies) {
        bool eligible = true;
        string reason = "";

        if (found->Cgpa < c.Mincgpa) {
            eligible = false;
            reason = "CGPA below requirement (" + to_string(c.Mincgpa) + " required)";
        }
        else if (found->Twelth < c.Mintwelth) {
            eligible = false;
            reason = "12th % below requirement (" + to_string(c.Mintwelth) + " required)";
        }
        else if (found->Tenth < c.Mintenth) {
            eligible = false;
            reason = "10th % below requirement (" + to_string(c.Mintenth) + " required)";
        }
        else if (found->Backlogs > c.Maxbacklogs) {
            eligible = false;
            reason = "Too many backlogs (max " + to_string(c.Maxbacklogs) + " allowed)";
        }

        if (eligible) {
            cout << "✓ ELIGIBLE   : " << c.Name << endl;
            anyEligible = true;
        } else {
            cout << "✗ NOT ELIGIBLE: " << c.Name << " — " << reason << endl;
        }
    }

    if (!anyEligible) {
        cout << "\nNot eligible for any company currently." << endl;
    }
}

int main() {
    loadStudents();
    loadCompanies();

    int choice;

    while (true) {
        cout << "\n=============================" << endl;
        cout << " Placement Eligibility System" << endl;
        cout << "=============================\n" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. View All Students" << endl;
        cout << "3. Search Student" << endl;
        cout << "4. Delete Student" << endl;
        cout << "5. Add Company" << endl;
        cout << "6. View All Companies" << endl;
        cout << "7. Delete Company" << endl;
        cout << "8. Check Eligibility" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: addCompany(); break;
            case 6: viewCompanies(); break;
            case 7: deleteCompany(); break;
            case 8: checkEligibility(); break;
            case 9:
                cout << "Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice." << endl;
        }
    }
}