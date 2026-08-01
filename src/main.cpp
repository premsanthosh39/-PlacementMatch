#include "csvutils.h"
#include <iostream>

int main() {
    std::string testLine = "21CS001,Rahul Sharma,8.5,CSE,0,\"C++,DSA,SQL\"";
    auto fields = parseCSVLine(testLine);
    for (const auto& f : fields) {
        std::cout << "[" << f << "]\n";
    }
    return 0;
}