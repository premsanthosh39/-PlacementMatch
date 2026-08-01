#include "csvutils.h"
std::vector<std::string> parseCSVLine(const std::string& line){
    std::vector<std::string> fields;
    std::string current;
    bool insidequotes = false;
    for(size_t i=0;i<line.size();i++){
        char c = line[i];
        if(c =='"'){
            insidequotes = !insidequotes;
        }
        else if(c == ',' && !insidequotes){
            fields.push_back(current);
            current.clear();
        }
        else{
            current += c;
        }
    }
    fields.push_back(current);
    return fields;
}
