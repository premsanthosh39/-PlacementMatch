#include "services/applicationsystem.h"
#include "services/eligibilitychecker.h"
#include<iostream>
#include<algorithm>

bool applicationexists(const std::vector<Application>& apps,const std::string& roll_no,const std::string& company_name){
    for(const auto& x: apps){
        if(x.get_roll_no() == roll_no && x.get_company_name() == company_name) return true;
    }
    return false;
}

bool applytocompany(std::vector<Application>& apps,std::vector<Student>& students,std::vector<Company>& companies,const std::string& roll_no,const std::string& company_name){
    Student* student = nullptr;
    Company* company = nullptr;

    for (auto& s : students) if (s.get_Roll_No() == roll_no) student = &s;
    for (auto& c : companies) if (c.get_Company_Name() == company_name) company = &c;

    if (!student) { std::cout << "Student not found.\n"; return false; }
    if (!company) { std::cout << "Company not found.\n"; return false; }

    if (applicationexists(apps, roll_no, company_name)) {
        std::cout << "Already applied to this company.\n";
        return false;
    }

    eligibilityresult r = eligibilitychecker(*student, *company);
    if (!r.eligible) {
        std::cout << "Cannot apply: " << r.result << "\n";
        return false;
    }

    apps.push_back(Application(roll_no, company_name));
    std::cout << "Application submitted successfully.\n";
    return true;
}

void viewapplicationforstudents(const std::vector<Application>& apps, const std::string& rollNo) {
    bool found = false;
    for (const auto& a : apps){
        if (a.get_roll_no() == rollNo){
            a.display();
            found = true;
        }
    }
    if (!found) std::cout << "No applications found for this student.\n";
}

bool updateApplicationStatus(std::vector<Application>& apps, const std::string& roll_no, const std::string& company_name, const std::string& newStatus) {
    for (auto& a : apps) {
        if (a.get_roll_no() == roll_no && a.get_company_name() == company_name) {
            a.set_status(newStatus);
            std::cout << "Application status updated to: " << newStatus << "\n";
            return true;
        }
    }
    std::cout << "Application not found.\n";
    return false;
}

bool deleteApplication(std::vector<Application>& apps, const std::string& roll_no, const std::string& company_name) {
    for (auto it = apps.begin(); it != apps.end(); ++it) {
        if (it->get_roll_no() == roll_no && it->get_company_name() == company_name) {
            apps.erase(it);
            std::cout << "Application withdrawn/deleted.\n";
            return true;
        }
    }
    std::cout << "Application not found.\n";
    return false;
}