#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct NODE {
    int key;
    NODE* p_next;
};

struct Stack {
    NODE* top;
};
Stack* initializeStack();
void push(Stack* s, int key);
int pop(Stack* s);
bool isEmpty(Stack* s);
void printStack(Stack* s, ofstream& fout);

Stack* initializeStack() {
    Stack* s = new Stack;
    s->top = nullptr;
    return s;
}

void push(Stack* s, int key) {
    if (s == nullptr) return;

    NODE* new_node = new NODE;
    new_node->key = key;
    new_node->p_next = s->top;
    s->top = new_node;
}

int pop(Stack* s) {
    if (s == nullptr || s->top == nullptr) {
        return -1;
    }

    NODE* temp = s->top;
    int popped_key = temp->key;
    s->top = temp->p_next;
    delete temp;
    return popped_key;
}

bool isEmpty(Stack* s) {
    return (s == nullptr || s->top == nullptr);
}

void printStack(Stack* s, ofstream& fout) {
    if (isEmpty(s)) {
        fout << "EMPTY" << endl;
    }
    else {
        NODE* current = s->top;
        while (current != nullptr) {
            fout << current->key << " ";
            current = current->p_next;
        }
        fout << endl;
    }
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    if (!fin.is_open()) {
        cout << "Cannot open input.txt" << endl;
        return 1;
    }
    if (!fout.is_open()) {
        cout << "Cannot open output.txt" << endl;
        return 1;
    }

    Stack* myStack = nullptr;
    string line;

    while (getline(fin, line)) {
        stringstream ss(line);
        string command;
        ss >> command;

        if (command == "init") {
            myStack = initializeStack();
            printStack(myStack, fout);
        }
        else if (command == "push") {
            int value;
            ss >> value;
            push(myStack, value);
            printStack(myStack, fout); 
        }
        else if (command == "pop") {
            pop(myStack);
            printStack(myStack, fout);
        }
    }

    fin.close();
    fout.close();

    while (!isEmpty(myStack)) {
        pop(myStack);
    }
    delete myStack;

    return 0;
}
