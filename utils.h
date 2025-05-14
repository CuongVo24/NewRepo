#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include "company.h"
using namespace std;

vector<Company> readCompanyList(const string& file_name);
long long hashString(const string& company_name);

#endif
