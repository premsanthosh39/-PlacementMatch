#include "application.h"
#include <iostream>

Application::Application(std::string roll_no, std::string company_name, std::string status)
    : roll_no(roll_no), company_name(company_name), status(status) {}

std::string Application::get_roll_no() const { return roll_no; }
std::string Application::get_company_name() const { return company_name; }
std::string Application::get_status() const { return status; }

void Application::set_status(const std::string& new_status) { status = new_status; }

void Application::display() const {
    std::cout << "RollNo: " << roll_no << " | Company: " << company_name
              << " | Status: " << status << "\n";
}