#include "company.h"
Company::Company(){
    Name : " ";
    Mincgpa : 0;
    Mintwelth : 0;
    Mintenth : 0;
    Maxbacklogs : 0;
}
void Company::input(){
    cout << "Enter Company Name: ";
    cin.ignore();
    getline(cin, Name);
    cout << "Enter Minimum CGPA Required: ";
    cin >> Mincgpa;
    cout << "Enter Minimum 12th % Required: ";
    cin >> Mintwelth;
    cout << "Enter Minimum 10th % Required: ";
    cin >> Mintenth;
    cout << "Enter Maximum Backlogs Allowed: ";
    cin >> Maxbacklogs;
}
void Company::display() {
    cout << "\n    Company Details     " << endl;
    cout << "Company Name   : " << Name << endl;
    cout << "Min CGPA       : " << Mincgpa << endl;
    cout << "Min 12th %     : " << Mintwelth << endl;
    cout << "Min 10th %     : " << Mintenth << endl;
    cout << "Max Backlogs   : " << Maxbacklogs << endl;
}