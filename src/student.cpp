#include "student.h"
#include<iostream>
//RETURNING THE GETTERS
Student::Student(std::string Roll_No,std::string Name,double Cgpa,std::string Branch,int Backlogs,std::vector<std::string> Skills) :Roll_No(Roll_No),Name(Name),Cgpa(Cgpa),Branch(Branch),Backlogs(Backlogs),Skills(Skills){}
std::string Student::get_Roll_No() const {return Roll_No; }
std::string Student::get_Name() const {return Name;}
double Student::get_Cgpa() const {return Cgpa;}
std::string Student::get_Branch() const {return Branch;}
int Student::get_Backlogs() const {return Backlogs;}
std::vector<std::string> Student::get_Skills() const {return Skills;}
//UPDATING THE SETTERS
void Student::set_Cgpa(double newcgpa){
    Cgpa = newcgpa;
}
void Student::set_Backlogs(int newbacklogs){
    Backlogs = newbacklogs;
}
//DISPLAYING THE DETAILS OF A STUDENT
void Student::display() const{
    std::cout<<"\n-----------------------------------------------------------------------------------------------------------------\n";
    std::cout<<"\n                                               THE STUDENT DETAILS                                               \n";
    std::cout<<"\n-----------------------------------------------------------------------------------------------------------------\n";
    std::cout<<"Name      : "<<Name<<std::endl;
    std::cout<<"Roll_No   : "<<Roll_No<<std::endl;
    std::cout<<"Cgpa      : "<<Cgpa<<std::endl;
    std::cout<<"Branch    : "<<Branch<<std::endl;
    std::cout<<"Backlogs  : "<<Backlogs<<std::endl;
    std::cout<<"Skills    : ";
    for(int i=0;i<Skills.size();i++){
        std::cout<<Skills[i];
        if(i != Skills.size()-1) std::cout<<" , ";
    }
    std::cout<<std::endl;
}
