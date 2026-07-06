#include "student.h"
Student::Student(){
    Name = "";
    Roll_No = 0;
    Cgpa = 0;
    Twelth = 0;
    Tenth = 0;
    Backlogs = 0;
}
void Student::input(){
    cout<<"Enter Name : ";
    cin.ignore();
    getline(cin,Name);
    cout<<"Enter Roll Number : ";
    cin>>Roll_No;
    cout<<"Enter Cgpa : ";
    cin>>Cgpa;
    cout<<"Enter 12th Percentage : ";
    cin>>Twelth;
    cout<<"Enter 10th Percentage: ";
    cin>>Tenth;
    cout<<"Enter Backlogs : ";
    cin>>Backlogs;
}
void Student::display(){
    cout<<"\n    Student Details   \n";
    cout<<"Name           : "<<Name<<endl;
    cout<<"Roll Number    : "<<Roll_No<<endl;
    cout<<"Cgpa           : "<<Cgpa<<endl;
    cout<<"12th %         : "<<Twelth<<endl;
    cout<<"10th %         : "<<Tenth<<endl;
    cout<<"Backlogs       : "<<Backlogs<<endl;
}