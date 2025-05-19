#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct NODE {
    int key;
    NODE* p_left;
    NODE* p_right;
};
NODE* createNode(int data);

vector<int> NLR(NODE* pRoot);
vector<int> LNR(NODE* pRoot);
vector<int> LRN(NODE* pRoot);

vector<vector<int>> LevelOrder(NODE* pRoot);
int countNode(NODE* pRoot);
int sumNode(NODE* pRoot);
int heightHelper(NODE* pRoot);
int heightNode(NODE* pRoot, int value);
int Level(NODE* pRoot, NODE* p, int level = 0);
int countLeaf(NODE* pRoot);


// 1. Tạo một NODE mới
NODE* createNode(int data) {
    NODE* newNode = new NODE{data, nullptr, nullptr};
    return newNode;
}

// 2. Duyệt tiền tự (NLR)
vector<int> NLR(NODE* pRoot) {
    vector<int> result;
    if (pRoot) {
        result.push_back(pRoot->key);
        vector<int> left = NLR(pRoot->p_left);
        vector<int> right = NLR(pRoot->p_right);
        result.insert(result.end(), left.begin(), left.end());
        result.insert(result.end(), right.begin(), right.end());
    }
    return result;
}

// 3. Duyệt trung tự (LNR)
vector<int> LNR(NODE* pRoot) {
    vector<int> result;
    if (pRoot) {
        vector<int> left = LNR(pRoot->p_left);
        result.insert(result.end(), left.begin(), left.end());
        result.push_back(pRoot->key);
        vector<int> right = LNR(pRoot->p_right);
        result.insert(result.end(), right.begin(), right.end());
    }
    return result;
}

// 4. Duyệt hậu tự (LRN)
vector<int> LRN(NODE* pRoot) {
    vector<int> result;
    if (pRoot) {
        vector<int> left = LRN(pRoot->p_left);
        vector<int> right = LRN(pRoot->p_right);
        result.insert(result.end(), left.begin(), left.end());
        result.insert(result.end(), right.begin(), right.end());
        result.push_back(pRoot->key);
    }
    return result;
}

// 5. Duyệt theo từng mức (Level Order)
vector<vector<int>> LevelOrder(NODE* pRoot) {
    vector<vector<int>> result;
    if (!pRoot) return result;

    queue<NODE*> q;
    q.push(pRoot);

    while (!q.empty()) {
        int size = q.size();
        vector<int> level;

        for (int i = 0; i < size; ++i) {
            NODE* current = q.front(); q.pop();
            level.push_back(current->key);
            if (current->p_left) q.push(current->p_left);
            if (current->p_right) q.push(current->p_right);
        }
        result.push_back(level);
    }

    return result;
}

// 6. Đếm số lượng NODE
int countNode(NODE* pRoot) {
    if (!pRoot) return 0;
    return 1 + countNode(pRoot->p_left) + countNode(pRoot->p_right);
}

// 7. Tính tổng các giá trị NODE
int sumNode(NODE* pRoot) {
    if (!pRoot) return 0;
    return pRoot->key + sumNode(pRoot->p_left) + sumNode(pRoot->p_right);
}

// 8. Tính chiều cao của NODE có giá trị nhất định
int heightHelper(NODE* pRoot) {
    if (!pRoot) return -1;
    return 1 + max(heightHelper(pRoot->p_left), heightHelper(pRoot->p_right));
}

int heightNode(NODE* pRoot, int value) {
    if (!pRoot) return -1;
    if (pRoot->key == value) return heightHelper(pRoot);
    int left = heightNode(pRoot->p_left, value);
    if (left != -1) return left;
    return heightNode(pRoot->p_right, value);
}

// 9. Tìm cấp độ của NODE (gốc là cấp 0)
int Level(NODE* pRoot, NODE* p, int level = 0) {
    if (!pRoot) return -1;
    if (pRoot == p) return level;
    int l = Level(pRoot->p_left, p, level + 1);
    if (l != -1) return l;
    return Level(pRoot->p_right, p, level + 1);
}

// 10. Đếm số lá (NODE không có con)
int countLeaf(NODE* pRoot) {
    if (!pRoot) return 0;
    if (!pRoot->p_left && !pRoot->p_right) return 1;
    return countLeaf(pRoot->p_left) + countLeaf(pRoot->p_right);
}
