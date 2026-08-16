#include "services/csvstorage.h"
#include "services/csvutils.h"
#include <fstream>
#include <iostream>

// ---------- APPLICATIONS ----------

std::vector<Application> loadApplications(const std::string& filename) {
    std::vector<Application> apps;
    std::ifstream file(filename);
    if (!file.is_open()) return apps;

    std::string line;
    std::getline(file, line); // skip header

    while (std::getline(file, line)) {
        if (line.empty()) continue;
        auto fields = parseCSVLine(line);
        if (fields.size() < 3) continue;

        apps.push_back(Application(fields[0], fields[1], fields[2]));
    }
    return apps;
}

void saveApplications(const std::vector<Application>& apps, const std::string& filename) {
    std::ofstream file(filename);
    file << "RollNo,CompanyName,Status\n";
    for (const auto& a : apps) {
        file << a.get_roll_no() << "," << a.get_company_name() << "," << a.get_status() << "\n";
    }
}

// ---------- STUDENTS ----------

std::vector<Student> loadStudents(const std::string& filename) {
    std::vector<Student> students;
    std::ifstream file(filename);
    if (!file.is_open()) return students;

    std::string line;
    std::getline(file, line); // skip header

    int lineNumber = 1;
    while (std::getline(file, line)) {
        lineNumber++;
        if (line.empty()) continue;

        try {
            auto fields = parseCSVLine(line);
            if (fields.size() < 7) {
                std::cout << "Warning: skipping malformed line " << lineNumber << " in " << filename << "\n";
                continue;
            }

            std::string rollNo = fields[0];
            std::string name = fields[1];
            double cgpa = std::stod(fields[2]);
            std::string branch = fields[3];
            int backlogs = std::stoi(fields[4]);

            std::vector<std::string> skills;
            std::string current;
            for (char c : fields[5]) {
                if (c == ',') { skills.push_back(current); current.clear(); }
                else current += c;
            }
            if (!current.empty()) skills.push_back(current);

            int gradYear = std::stoi(fields[6]);

            students.push_back(Student(rollNo, name, cgpa, branch, backlogs, skills, gradYear));

        } catch (const std::exception& e) {
            std::cout << "Warning: could not parse line " << lineNumber
                      << " in " << filename << " (" << e.what() << "). Skipping.\n";
            continue;
        }
    }
    return students;
}

void saveStudents(const std::vector<Student>& students, const std::string& filename) {
    std::ofstream file(filename);
    file << "RollNo,Name,CGPA,Branch,Backlogs,Skills,GraduationYear\n";

    for (const auto& s : students) {
        file << s.get_Roll_No() << "," << s.get_Name() << "," << s.get_Cgpa() << ","
             << s.get_Branch() << "," << s.get_Backlogs() << ",\"";
        auto skills = s.get_Skills();
        for (size_t i = 0; i < skills.size(); i++) {
            file << skills[i];
            if (i != skills.size() - 1) file << ",";
        }
        file << "\"," << s.get_Graduation_Year() << "\n";
    }
}

// ---------- COMPANIES ----------

std::vector<Company> loadCompanies(const std::string& filename) {
    std::vector<Company> companies;
    std::ifstream file(filename);
    if (!file.is_open()) return companies;

    std::string line;
    std::getline(file, line); // skip header

    int lineNumber = 1;
    while (std::getline(file, line)) {
        lineNumber++;
        if (line.empty()) continue;

        try {
            auto fields = parseCSVLine(line);
            if (fields.size() < 7) {
                std::cout << "Warning: skipping malformed line " << lineNumber << " in " << filename << "\n";
                continue;
            }

            std::string name = fields[0];
            double minCgpa = std::stod(fields[1]);
            int maxBacklogs = std::stoi(fields[2]);

            std::vector<std::string> branches;
            std::string current;
            for (char c : fields[3]) {
                if (c == ',') { branches.push_back(current); current.clear(); }
                else current += c;
            }
            if (!current.empty()) branches.push_back(current);

            double package = std::stod(fields[4]);
            std::string role = fields[5];
            int eligibleYear = std::stoi(fields[6]);

            companies.push_back(Company(name, minCgpa, maxBacklogs, branches, package, role, eligibleYear));

        } catch (const std::exception& e) {
            std::cout << "Warning: could not parse line " << lineNumber
                      << " in " << filename << " (" << e.what() << "). Skipping.\n";
            continue;
        }
    }
    return companies;
}

void saveCompanies(const std::vector<Company>& companies, const std::string& filename) {
    std::ofstream file(filename);
    file << "Name,MinCGPA,MaxBacklogs,Branches,Package,Role,EligibleGradYear\n";
    for (const auto& c : companies) {
        file << c.get_Company_Name() << "," << c.get_min_Cgpa() << "," << c.get_max_Backlogs() << ",\"";
        auto branches = c.get_eligible_Branches();
        for (size_t i = 0; i < branches.size(); i++) {
            file << branches[i];
            if (i != branches.size() - 1) file << ",";
        }
        file << "\"," << c.get_Packages() << "," << c.get_Role() << "," << c.get_Eligible_Graduation_Year() << "\n";
    }
}