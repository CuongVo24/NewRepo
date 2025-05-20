#include<iostream>

using namespace std;


struct NODE {
    int key;
    NODE* p_left;
    NODE* p_right;
    int height;
};
//1.Tạo node
NODE* createNode(int data) {
    return new NODE{data, nullptr, nullptr, 0};
}

//Các hàm phụ trợ cho avl

//Cập nhật chiều cao
int getHeight(NODE* node) {
    return node ? node->height : -1;
}
void updateHeight(NODE* node) {
    node->height = 1 + std::max(getHeight(node->p_left), getHeight(node->p_right));
}

//Tính hệ số cân bằng
int getBalance(NODE* node) {
    return node ? getHeight(node->p_left) - getHeight(node->p_right) : 0;
}

//Xoay trái
NODE* rotateLeft(NODE* x) {
    NODE* y = x->p_right;
    NODE* T2 = y->p_left;

    y->p_left = x;
    x->p_right = T2;

    updateHeight(x);
    updateHeight(y);
    return y;
}

//Xoay phải
NODE* rotateRight(NODE* y) {
    NODE* x = y->p_left;
    NODE* T2 = x->p_right;

    x->p_right = y;
    y->p_left = T2;

    updateHeight(y);
    updateHeight(x);
    return x;
}

//2. Chèn vào cây AVL
void Insert(NODE* &pRoot, int x) {
    if (!pRoot) {
        pRoot = createNode(x);
        return;
    }

    if (x < pRoot->key)
        Insert(pRoot->p_left, x);
    else if (x > pRoot->key)
        Insert(pRoot->p_right, x);
    else
        return; // Không chèn trùng

    updateHeight(pRoot);
    int balance = getBalance(pRoot);

    // Left Left
    if (balance > 1 && x < pRoot->p_left->key)
        pRoot = rotateRight(pRoot);

    // Right Right
    else if (balance < -1 && x > pRoot->p_right->key)
        pRoot = rotateLeft(pRoot);

    // Left Right
    else if (balance > 1 && x > pRoot->p_left->key) {
        pRoot->p_left = rotateLeft(pRoot->p_left);
        pRoot = rotateRight(pRoot);
    }

    // Right Left
    else if (balance < -1 && x < pRoot->p_right->key) {
        pRoot->p_right = rotateRight(pRoot->p_right);
        pRoot = rotateLeft(pRoot);
    }
}

//3. Xóa khỏi cây AVL
//Hàm phụ tìm node nhỏ nhất
NODE* findMin(NODE* node) {
    while (node && node->p_left)
        node = node->p_left;
    return node;
}
void Remove(NODE* &pRoot, int x) {
    if (!pRoot) return;

    if (x < pRoot->key)
        Remove(pRoot->p_left, x);
    else if (x > pRoot->key)
        Remove(pRoot->p_right, x);
    else {
        // Node có 1 hoặc 0 con
        if (!pRoot->p_left || !pRoot->p_right) {
            NODE* temp = pRoot->p_left ? pRoot->p_left : pRoot->p_right;
            delete pRoot;
            pRoot = temp;
        }
        else {
            // Node có 2 con
            NODE* temp = findMin(pRoot->p_right);
            pRoot->key = temp->key;
            Remove(pRoot->p_right, temp->key);
        }
    }

    if (!pRoot) return;

    updateHeight(pRoot);
    int balance = getBalance(pRoot);

    // Left Left
    if (balance > 1 && getBalance(pRoot->p_left) >= 0)
        pRoot = rotateRight(pRoot);

    // Left Right
    else if (balance > 1 && getBalance(pRoot->p_left) < 0) {
        pRoot->p_left = rotateLeft(pRoot->p_left);
        pRoot = rotateRight(pRoot);
    }

    // Right Right
    else if (balance < -1 && getBalance(pRoot->p_right) <= 0)
        pRoot = rotateLeft(pRoot);

    // Right Left
    else if (balance < -1 && getBalance(pRoot->p_right) > 0) {
        pRoot->p_right = rotateRight(pRoot->p_right);
        pRoot = rotateLeft(pRoot);
    }
}

//4. Kiểm tra cây có phải AVL không
bool isAVL(NODE* pRoot) {
    if (!pRoot) return true;

    int balance = getBalance(pRoot);
    if (abs(balance) > 1) return false;

    return isAVL(pRoot->p_left) && isAVL(pRoot->p_right);
}

