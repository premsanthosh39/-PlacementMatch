#ifndef COMPANYREGISTRATION_H
#define COMPANYREGISTRATION_H

#include "company.h"
#include <vector>

bool companynameexists(const std::vector<Company>& companies,
                       const std::string& name);

void registercompanies(std::vector<Company>& companies);

#endif