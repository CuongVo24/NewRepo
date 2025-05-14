#include "hash_table.h"
#include "utils.h"

using namespace std;

HashTable* createHashTable(const vector<Company>& list_company) {
    HashTable* hash_table = new HashTable(2000);
    for (const Company& c : list_company) {
        insert(hash_table, c);
    }
    return hash_table;
}

void insert(HashTable* hash_table, const Company& company) {
    long long idx = hashString(company.name);
    hash_table->table[idx].push_back(company);
}

Company* search(HashTable* hash_table, const string& company_name) {
    long long idx = hashString(company_name);
    for (Company& c : hash_table->table[idx]) {
        if (c.name == company_name)
            return &c;
    }
    return nullptr;
}

