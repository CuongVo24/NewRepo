#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct NODE {
    int key;
    NODE* p_next;
};

struct Queue {
    NODE* head;
    NODE* tail;
};

Queue* initializeQueue();
void enqueue(Queue* q, int key);
int dequeue(Queue* q);
int size(Queue* q);
bool isEmpty(Queue* q);
void printQueue(Queue* q, ofstream& fout);

Queue* initializeQueue() {
    Queue* q = new Queue;
    q->head = q->tail = nullptr;
    return q;
}

void enqueue(Queue* q, int key) {
    if (q == nullptr) return;

    NODE* new_node = new NODE;
    new_node->key = key;
    new_node->p_next = nullptr;

    if (q->tail == nullptr) {
        q->head = q->tail = new_node;
    }
    else {
        q->tail->p_next = new_node;
        q->tail = new_node;
    }
}

int dequeue(Queue* q) {
    if (q == nullptr || q->head == nullptr) {
        return -1;
    }

    NODE* temp = q->head;
    int dequeued_key = temp->key;
    q->head = temp->p_next;

    if (q->head == nullptr) {
        q->tail = nullptr;
    }

    delete temp;
    return dequeued_key;
}

int size(Queue* q) {
    int count = 0;
    NODE* current = q->head;
    while (current != nullptr) {
        count++;
        current = current->p_next;
    }
    return count;
}

bool isEmpty(Queue* q) {
    return (q == nullptr || q->head == nullptr);
}

void printQueue(Queue* q, ofstream& fout) {
    if (isEmpty(q)) {
        fout << "EMPTY" << endl;
    }
    else {
        NODE* current = q->head;
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

    if (!fin.is_open() || !fout.is_open()) {
        cout << "Cannot open file!" << endl;
        return 1;
    }

    Queue* q = nullptr;
    string command;
    while (fin >> command) {
        if (command == "init") {
            q = initializeQueue();
            printQueue(q, fout);
        }
        else if (command == "enqueue") {
            int value;
            fin >> value;
            enqueue(q, value);
            printQueue(q, fout);
        }
        else if (command == "dequeue") {
            dequeue(q);
            printQueue(q, fout);
        }
    }

    while (!isEmpty(q)) {
        dequeue(q);
    }
    delete q;

    fin.close();
    fout.close();

    return 0;
}
