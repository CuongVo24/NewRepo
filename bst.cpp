#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct NODE {
    int key;
    NODE* p_left;
    NODE* p_right;
};
NODE* Search(NODE* pRoot, int x);
void Insert(NODE* &pRoot, int x);
NODE* findMin(NODE* p);
void Remove(NODE* &pRoot, int x);
NODE* createTree(int a[], int n);
void removeTree(NODE* &pRoot);
int Height(NODE* pRoot);
int countLess(NODE* pRoot, int x);
int countGreater(NODE* pRoot, int x);
bool isBSTUtil(NODE* node, int minVal, int maxVal);
bool isFullBST(NODE* pRoot);



//1. Tìm node theo giá trị
NODE* Search(NODE* pRoot, int x) {
    if (!pRoot || pRoot->key == x) return pRoot;
    if (x < pRoot->key)
        return Search(pRoot->p_left, x);
    else
        return Search(pRoot->p_right, x);
}

//2.Thêm node vào BST
void Insert(NODE* &pRoot, int x) {
    if (!pRoot) {
        pRoot = new NODE{x, nullptr, nullptr};
        return;
    }
    if (x < pRoot->key)
        Insert(pRoot->p_left, x);
    else if (x > pRoot->key)
        Insert(pRoot->p_right, x);
}
//3.Xóa node khỏi BST
NODE* findMin(NODE* p) {
    while (p && p->p_left)
        p = p->p_left;
    return p;
}

void Remove(NODE* &pRoot, int x) {
    if (!pRoot) return;

    if (x < pRoot->key)
        Remove(pRoot->p_left, x);
    else if (x > pRoot->key)
        Remove(pRoot->p_right, x);
    else {
        // Node cần xóa có 0 hoặc 1 con
        if (!pRoot->p_left) {
            NODE* temp = pRoot;
            pRoot = pRoot->p_right;
            delete temp;
        } else if (!pRoot->p_right) {
            NODE* temp = pRoot;
            pRoot = pRoot->p_left;
            delete temp;
        } else {
            // Node có 2 con
            NODE* temp = findMin(pRoot->p_right);
            pRoot->key = temp->key;
            Remove(pRoot->p_right, temp->key);
        }
    }
}

//4.Tạo BST từ mảng
NODE* createTree(int a[], int n) {
    NODE* root = nullptr;
    for (int i = 0; i < n; ++i)
        Insert(root, a[i]);
    return root;
}

//5.Xóa toàn bộ cây
void removeTree(NODE* &pRoot) {
    if (!pRoot) return;
    removeTree(pRoot->p_left);
    removeTree(pRoot->p_right);
    delete pRoot;
    pRoot = nullptr;
}

//6.Tính chiều cao của cây
int Height(NODE* pRoot) {
    if (!pRoot) return -1;
    return 1 + std::max(Height(pRoot->p_left), Height(pRoot->p_right));
}

//7.Đếm số node có giá trị nhỏ hơn x
int countLess(NODE* pRoot, int x) {
    if (!pRoot) return 0;
    if (pRoot->key < x)
        return 1 + countLess(pRoot->p_left, x) + countLess(pRoot->p_right, x);
    else
        return countLess(pRoot->p_left, x);
}

//8.Đếm node có giá trị lớn hơn x
int countGreater(NODE* pRoot, int x) {
    if (!pRoot) return 0;
    if (pRoot->key > x)
        return 1 + countGreater(pRoot->p_left, x) + countGreater(pRoot->p_right, x);
    else
        return countGreater(pRoot->p_right, x);
}

//9.Kiểm tra có phải BST không
bool isBSTUtil(NODE* node, int minVal, int maxVal) {
    if (!node) return true;
    if (node->key <= minVal || node->key >= maxVal)
        return false;
    return isBSTUtil(node->p_left, minVal, node->key) &&
           isBSTUtil(node->p_right, node->key, maxVal);
}

bool isBST(NODE* pRoot) {
    return isBSTUtil(pRoot, INT_MIN, INT_MAX);
}

//10.Kiểm tra có phải BST đầy đủ
bool isFullBST(NODE* pRoot) {
    if (!pRoot) return true;
    if (!pRoot->p_left && !pRoot->p_right) return true;
    if (pRoot->p_left && pRoot->p_right)
        return isFullBST(pRoot->p_left) && isFullBST(pRoot->p_right);
    return false;
}
