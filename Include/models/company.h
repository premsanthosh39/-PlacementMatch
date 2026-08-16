#ifndef COMPANY_H
#define COMPANY_H
#include<vector>
#include<string>
class Company{
private:
    std::string Company_Name;
    double min_Cgpa;
    int max_Backlogs;
    std::vector<std::string> eligible_Branches;
    double Packages;
    std::string Role;
    int Eligible_Graduation_Year;
public:
    //CONSTRUCTORS
    Company(std::string Company_Name,double min_Cgpa,int max_Backlogs,std::vector<std::string> eligible_Branches,double Packages,std::string Role,int Eligible_Graduation_Year);
    //GETTERS
    std::string get_Company_Name() const;
    double get_min_Cgpa() const;
    int get_max_Backlogs() const;
    std::vector<std::string> get_eligible_Branches() const;
    double get_Packages() const;
    std::string get_Role() const;
    int get_Eligible_Graduation_Year() const;
    //SETTERS
    void set_Cgpa(double new_Cgpa);
    void set_max_Backlogs(int new_max_Backlogs);
    void set_Packages(double new_Packages);
    void set_eligible_Branches(std::vector<std::string> newBranches);
    void set_Eligible_Graduation_Year(int newYear);  
    //UTILITY FUNCTION
    bool isbrancheligible(const std::string& branch) const;
    //DISPLAY
    void display() const;
};
#endif