#include "models/company.h"
#include<iostream>
#include<algorithm>//FOR FIND FUNCTION WE USED IT 
//CONSTRUCTOR INITIALIZATION
Company::Company(std::string Company_Name,double min_Cgpa,int max_Backlogs,std::vector<std::string> eligible_Branches,double Packages,std::string Role,int Eligible_Graduation_Year) :Company_Name(Company_Name),min_Cgpa(min_Cgpa),max_Backlogs(max_Backlogs),eligible_Branches(eligible_Branches),Packages(Packages),Role(Role),Eligible_Graduation_Year(Eligible_Graduation_Year) {}
//RETURNS THE GETTERS
std::string Company::get_Company_Name() const {return Company_Name;} 
double Company::get_min_Cgpa() const {return min_Cgpa;}
int Company::get_max_Backlogs() const {return max_Backlogs;}
std::vector<std::string> Company::get_eligible_Branches() const {return eligible_Branches;}
double Company::get_Packages() const {return Packages;}
std::string Company::get_Role() const {return Role;}
int Company::get_Eligible_Graduation_Year() const {return Eligible_Graduation_Year;}

//UPDATING THE SETTERS
void Company::set_Cgpa(double newcgpa){
    min_Cgpa = newcgpa;
}
void Company::set_max_Backlogs(int newbacklogs){
    max_Backlogs = newbacklogs;
}
void Company::set_Packages(double newpackages){
    Packages = newpackages;
}
void Company::set_eligible_Branches(std::vector<std::string> newbranches){
    eligible_Branches = newbranches;
}

void Company::set_Eligible_Graduation_Year(int newYear){ Eligible_Graduation_Year = newYear; }
//DISPLAYING THE COMPANY DETAILS
void Company::display() const{
    std::cout<<"\n-----------------------------------------------------------------------------------------------------------------\n";
    std::cout<<"\n                                               THE COMPANY DETAILS                                               \n";
    std::cout<<"\n-----------------------------------------------------------------------------------------------------------------\n";
    std::cout<<"Company_Name      : "<<Company_Name<<std::endl;
    std::cout<<"min_Cgpa          :  "<<min_Cgpa<<std::endl;
    std::cout<<"max_Backlogs      :  "<<max_Backlogs<<std::endl;
    std::cout<<"eligible_Branches : ";
    for(int i=0;i<eligible_Branches.size();i++){
        std::cout<<eligible_Branches[i];
        if(i != eligible_Branches.size()-1) std::cout<<" , ";
    }
    std::cout<<std::endl;
    std::cout<<"Packages (In LPA) : "<<Packages<<std::endl;
    std::cout<<"Role              : "<<Role<<std::endl;
    std::cout<<"Eligible Grad Year  : "<<Eligible_Graduation_Year<<std::endl;
}
//UTILITY FUNCTION CHECKING
bool Company::isbrancheligible(const std::string& branch) const{
    return std::find(eligible_Branches.begin(),eligible_Branches.end(),branch) != eligible_Branches.end();
}