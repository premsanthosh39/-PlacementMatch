#ifndef APPLICATION_H
#define APPLICATION_H
#include <string>

class Application {
private:
    std::string roll_no;
    std::string company_name;
    std::string status;

public:
    Application(std::string roll_no, std::string company_name, std::string status = "Applied");

    std::string get_roll_no() const;
    std::string get_company_name() const;
    std::string get_status() const;

    void set_status(const std::string& new_status);

    void display() const;
};
#endif