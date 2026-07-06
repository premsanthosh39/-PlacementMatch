#ifndef COMPANY_H
#define COMPANY_H
#include<iostream>
#include<string>
using namespace std;
class Company{
public:
    string Name;
    float Mincgpa;
    float Mintenth;
    float Mintwelth;
    int Maxbacklogs;
    Company();
    void input();
    void display();
};
#endif