#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "company.h"
#include <vector>
#include <list>
#include <string>

using namespace std;

struct HashTable {
    vector<list<Company>> table;
    int size;

    HashTable(int sz) : size(sz) {
        table.resize(sz);
    }
};

HashTable* createHashTable(const vector<Company>& list_company);
void insert(HashTable* hash_table, const Company& company);
Company* search(HashTable* hash_table, const string& company_name);

#endif
