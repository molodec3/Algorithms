/*
2_2. Вычислить количество узлов в самом широком слое
декартового дерева и количество узлов в самом широком
слое наивного дерева поиска. Вывести их разницу. Разница
может быть отрицательна.
*/

#include <iostream>
#include <queue>

struct Binary_Node {
    int Data;
    Binary_Node* Left;
    Binary_Node* Right;
    Binary_Node(int d) : Data(d), Left(nullptr), Right(nullptr) {}
};

void insert_binary (Binary_Node*& root, int value) {
    if (root == nullptr) {
        root = new Binary_Node(value);
        return;
    }
    if (root->Data > value) {
        insert_binary(root->Left, value);
    }
    else {
        insert_binary(root->Right, value);
    }
}

struct Treap_Node {
    int Key;
    int Priority;
    Treap_Node* Left;
    Treap_Node* Right;
    Treap_Node(int x, int y) : Key(x), Priority(y), Left(nullptr), Right(nullptr) {}
};

void Split (Treap_Node* root, int key, Treap_Node*& left, Treap_Node*& right) {
    if (root == nullptr) {
        left = nullptr;
        right = nullptr;
    }
    else if (root->Key < key) {
        Split(root->Right, key, root->Right, right);
        left = root;
    }
    else {
        Split(root->Left, key, left, root->Left);
        right = root;
    }
}

void insert_treap (Treap_Node*& root, int x, int y) {
    Treap_Node* node = root;
    Treap_Node* parent = root;
    while (node != nullptr && node->Priority >= y) {
        parent = node;
        if (x < node->Key) {
            node = node->Left;
        }
        else {
            node = node->Right;
        }
    }
    Treap_Node* new_node = new Treap_Node(x, y);
    Split(node, x, new_node->Left, new_node->Right);
    if (node == root) {
        root = new_node;
    }
    else if (parent->Key <= x) {
        parent->Right = new_node;
    }
    else {
        parent->Left = new_node;
    }
}

template <typename T>
int count_width (T* root) {
    std::queue<T*> q;
    q.push(root);
    int result = 0;
    while (!q.empty()) {
        int width = q.size();
        if (width > result) {
            result = width;
        }
        for (int i = 0; i < width; ++i) {
            T* node = q.front();
            q.pop();
            if (node->Left != nullptr) {
                q.push(node->Left);
            }
            if (node->Right != nullptr) {
                q.push(node->Right);
            }
            delete node;
        }
    }
    return result;
}

int main() {
    int n, x, y;
    std::cin >> n;
    std::cin >> x >> y;
    Treap_Node* treap = new Treap_Node(x, y);
    Binary_Node* bin_tree = new Binary_Node(x);
    for (int i = 1; i < n; ++i) {
        std::cin >> x >> y;
        insert_treap(treap, x, y);
        insert_binary(bin_tree, x);
    }
    std::cout << count_width<Treap_Node>(treap) - count_width<Binary_Node>(bin_tree) << std::endl;
    return 0;
}