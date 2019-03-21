/*
1_4. Выведите элементы в порядке level-order (по слоям, “в ширину”).
*/

#include <iostream>
#include <queue>

struct Node {
    int Data;
    Node* Left;
    Node* Right;
    Node(int d) : Data(d), Left(nullptr), Right(nullptr) {}
};

void insert (Node*& node, int value) {
    if (node == nullptr) {
        node = new Node(value);
        return;
    }
    if (node->Data > value) {
        insert(node->Left, value);
    }
    else {
        insert(node->Right, value);
    }
}

void bfs(Node* root) {
    std::queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* node = q.front();
        q.pop();
        std::cout << node->Data << " ";
        if (node->Left != nullptr) {
            q.push(node->Left);
        }
        if (node->Right != nullptr) {
            q.push(node->Right);
        }
        delete node;
    }
}

int main() {
    int n;
    std::cin >> n;
    int value;
    std::cin >> value;
    Node* binary_tree = new Node(value);
    for (int i = 1; i < n; ++i) {
        std::cin >> value;
        insert(binary_tree, value);
    }
    bfs(binary_tree);
    std::cout << std::endl;
    return 0;
}