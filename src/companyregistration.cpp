#include "companyregistration.h" 
#include<iostream>
#include<limits>
bool companynameexists(const std::vector<Company>& companies,const std::string& name){
    for(const auto& x:companies){
        if(x.get_Company_Name() == name){ 
            return true;
        }
    }
    return false;
}
void registercompanies(std::vector<Company>& companies){
    std::string name,role;
    double package,min_cgpa;
    int max_backlogs;
    std::vector<std::string> branches;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    std::cout<<"Enter your Company Name : ";
    std::getline(std::cin,name);

    if(companynameexists(companies,name)){
        std::cout<<"This Company already registered\n";
        return;
    }
    while(true){
        std::cout<<"Enter the min_cgpa :";
        if(!(std::cin>>min_cgpa)||min_cgpa<0||min_cgpa>10){
            std::cout<<"Invalid cgpa you have entered\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
        else break;
    }
    while(true){
        std::cout<<"Enter the max_backlogs : ";
        if(!(std::cin>>max_backlogs) ||max_backlogs<0){
            std::cout<<"Invalid value \n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
        else break;
    } 
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter Eligible Branches (comma-separated, e.g. CSE,ECE): ";
    std::string branchline;
    std::getline(std::cin,branchline);
    std::string current;
    for(auto c: branchline){
        if(c == ','){
            branches.push_back(current);
            current.clear();
        }
        else{
            current += c;
        }
    }
    if(!current.empty()) branches.push_back(current);

    while (true) {
        std::cout << "Enter Package (LPA): ";
        if (!(std::cin >> package) || package < 0) {
            std::cout << "Invalid value. Try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else break;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter Role: ";
    std::getline(std::cin, role);

    int eligibleYear;
    while (true) {
        std::cout << "Enter Eligible Graduation Year (e.g. 2026): ";
        if (!(std::cin >> eligibleYear) || eligibleYear < 2000 || eligibleYear > 2100) {
            std::cout << "Invalid year. Try again.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else break;
    }

    companies.push_back(Company(name, min_cgpa, max_backlogs, branches, package, role,eligibleYear));
    std::cout << "Company registered successfully.\n";
}
