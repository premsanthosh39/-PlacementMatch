#ifndef APPLICATION_H
#define APPLICATION_H
#include<string>
class Application{
private:
    std::string Roll_No;
    std::string Company_Name;
    std::string status;
public:
    Application(std::string Roll_No,std::string Company_Name,std::string status = "Applied");
    std::string get_roll_no() const;
    std::string get_company_name() const;
    std::string get_status() const;

    void set_status(const std::string& status);
    void display() const;
};
#endif