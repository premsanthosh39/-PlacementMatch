
#ifndef STUDENT_H
#define STUDENT_H
#include<iostream>
#include<string>
using namespace std; 
class Student{
public:
    string Name;
    int Roll_No;
    float Cgpa;
    float Twelth;
    float Tenth;
    int Backlogs;
    Student();
    void input();
    void display();
};
#endif