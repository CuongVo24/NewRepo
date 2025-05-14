#include <iostream>
#include <fstream>
#include "utils.h"
#include "hash_table.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: ./main MST.txt input.txt output.txt\n";
        return 1;
    }

    string mst_file = argv[1];
    string input_file = argv[2];
    string output_file = argv[3];

    vector<Company> companies = readCompanyList(mst_file);
    HashTable* table = createHashTable(companies);

    ifstream in(input_file);
    ofstream out(output_file);

    string name;
    while (getline(in, name)) {
        Company* result = search(table, name);
        if (result) {
            out << result->name << "|" << result->profit_tax << "|" << result->address << "\n";
        }
    }

    delete table;
    return 0;
}
