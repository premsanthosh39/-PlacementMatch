#include "services/eligibilitychecker.h"
eligibilityresult eligibilitychecker(const Student& s,const Company& c){
    if(s.get_Cgpa()<c.get_min_Cgpa()){
        return {false , "Cgpa is below company requirements("+std::to_string(c.get_min_Cgpa())+")\n"};
    }
    if(s.get_Backlogs()>c.get_max_Backlogs()){
        return {false,"you have exceeded the company backlogs("+std::to_string(c.get_max_Backlogs())+")\n"};
    }
    if(!c.isbrancheligible(s.get_Branch())){
        return {false,"student branch("+s.get_Branch()+") is not eligible for this company\n"};
    }
    if (s.get_Graduation_Year() != c.get_Eligible_Graduation_Year()) {
        return { false, "Graduation year mismatch (company recruits " + std::to_string(c.get_Eligible_Graduation_Year()) + " batch)" };
    }
    return {true,"you are elibile for this company\n"};
}