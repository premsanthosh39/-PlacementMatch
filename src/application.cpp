#include "application.h"
#include "iostream"
Application::Application(std::string roll_no,std::string company_name,std::string status) :Roll_No(roll_no),Company_Name(company_name),status(status) {}

std::string Application::get_roll_no() const{
    return Roll_No;
}
std::string Application::get_company_name() const{
    return Company_Name;
}
std::string Application::get_status() const{
    return status;
}

void Application::set_status(const std::string& newstatus){
    status = newstatus;
}

void Application::display() const{
    std::cout<<"Roll number : "<<Roll_No;
    std::cout<<"Company name : "<<Company_Name;
    std::cout<<"Status is : "<<status;
}