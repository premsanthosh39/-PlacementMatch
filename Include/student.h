#ifndef STUDENT_H
#define STUDENT_H
#include<string>
#include<vector>
class Student{
private:
    std::string Roll_No;
    std::string Name;
    double Cgpa;
    std::string Branch;
    int Backlogs;
    std::vector<std::string> Skills;
public:
    //CONSTRUCTOR
    Student(std::string Roll_No,std::string Name,double Cgpa,std::string Branch,int Backlogs,std::vector<std::string> Skills);
    //GETTERS
    std::string get_Roll_No() const;
    std::string get_Name() const;
    double get_Cgpa() const;
    std::string get_Branch() const;
    int get_Backlogs() const;
    std::vector<std::string> get_Skills() const;
    // SETTERS
    void set_Cgpa(double newCgpa);
    void set_Backlogs(int newBacklogs);
    //DISPLAY
    void display() const;
};
#endif