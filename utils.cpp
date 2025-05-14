#include "utils.h"
#include <fstream>
#include <sstream>

using namespace std;

vector<Company> readCompanyList(const string& file_name) {
    vector<Company> list;
    ifstream file(file_name);
    string line;

    getline(file, line); // Skip header

    while (getline(file, line)) {
        stringstream ss(line);
        string name, tax, address;

        getline(ss, name, '|');
        getline(ss, tax, '|');
        getline(ss, address);

        list.push_back({name, tax, address});
    }

    return list;
}

long long hashString(const string& company_name) {
    const int p = 31;
    const int m = 2000;
    long long hash_value = 0;
    long long power_of_p = 1;

    string s = company_name.size() > 20
        ? company_name.substr(company_name.size() - 20)
        : company_name;

    for (int i = 0; i < s.length(); ++i) {
        hash_value = (hash_value + (s[i] * power_of_p) % m) % m;
        power_of_p = (power_of_p * p) % m;
    }

    return hash_value;
}
