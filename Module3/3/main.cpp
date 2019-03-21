/*
3_1. Солдаты. В одной военной части решили построить в одну
шеренгу по росту. Т.к. часть была далеко не образцовая, то
солдаты часто приходили не вовремя, а то их и вовсе
приходилось выгонять из шеренги за плохо начищенные сапоги.
Однако солдаты в процессе прихода и ухода должны были всегда
быть выстроены по росту – сначала самые высокие, а в конце –
самые низкие. За расстановку солдат отвечал прапорщик,
который заметил интересную особенность – все солдаты в части
разного роста. Ваша задача состоит в том, чтобы помочь
прапорщику правильно расставлять солдат, а именно для
каждого приходящего солдата указывать, перед каким солдатом
в строе он должен становится. Требуемая скорость выполнения
команды - O(log n).
 */

#include <iostream>
#include <stack>

struct AVL_Node {
    int Data;
    int height;
    int children;
    AVL_Node* Left;
    AVL_Node* Right;
    AVL_Node(int d) : Data (d), height(1), children(1), Left(nullptr), Right(nullptr) {}
};

int count_children (AVL_Node*& root) {
    if (root == nullptr) {
        return 0;
    }
    else {
        return root->children;
    }
}

int count_height (AVL_Node*& root) {
    if (root == nullptr) {
        return 0;
    }
    else {
        return root->height;
    }
}

void rotate_Left (AVL_Node*& root) {
    AVL_Node* tmp = root;
    root = root->Right;
    tmp->Right = root->Left;
    root->Left = tmp;
    root->Left->height = std::max(count_height(root->Left->Left), count_height(root->Left->Right)) + 1;
    root->height = std::max(count_height(root->Left), count_height(root->Right)) + 1;
    root->Left->children = count_children(root->Left->Left) + count_children(root->Left->Right) + 1;
    root->children = count_children(root->Right) + count_children(root->Left) + 1;
}

void rotate_Right (AVL_Node*& root) {
    AVL_Node* tmp = root;
    root = root->Left;
    tmp->Left = root->Right;
    root->Right = tmp;
    root->Right->height = std::max(count_height(root->Right->Left), count_height(root->Right->Right)) + 1;
    root->height = std::max(count_height(root->Left), count_height(root->Right)) + 1;
    root->Right->children = count_children(root->Right->Left) + count_children(root->Right->Right) + 1;
    root->children = count_children(root->Right) + count_children(root->Left) + 1;
}

void big_rotate_Left (AVL_Node*& root) {
    rotate_Left(root);
    rotate_Left(root->Left);
    rotate_Right(root);
}

void big_rotate_Right (AVL_Node*& root) {
    rotate_Right(root);
    rotate_Right(root->Right);
    rotate_Left(root);
}

void balance (AVL_Node*& root) {
    if (root != nullptr) {
        root->height = std::max(count_height(root->Right), count_height(root->Left)) + 1;
        if (count_height(root->Left) - count_height(root->Right) == -2) {
            if (count_height(root->Right->Left) <= count_height(root->Right->Right)) {
                rotate_Left(root);
            }
            else {
                big_rotate_Left(root);
            }
        }
        else if (count_height(root->Left) - count_height(root->Right) == 2) {
            if (count_height(root->Left->Right) <= count_height(root->Left->Left)) {
                rotate_Right(root);
            }
            else {
                big_rotate_Right(root);
            }
        }
    }
}

void insert (AVL_Node*& root, int value, int& result) {
    if (root == nullptr) {
        root = new AVL_Node(value);
    }
    else {
        ++(root->children);
        if (root->Data <= value) {
            insert(root->Right, value, result);
        }
        else {
            result += count_children(root->Right) + 1;
            insert(root->Left, value, result);
        }
        balance(root);
    }
}

void erase (AVL_Node*& root, int pos) {
    if (root != nullptr) {
        int r_elem = count_children(root->Right);
        if (r_elem < pos) {
            --root->children;
            pos -= (r_elem + 1);
            erase(root->Left, pos);
        }
        else if (r_elem > pos) {
            --root->children;
            erase(root->Right, pos);
        }
        else {
            if (root->Left == nullptr) {
                if (root->Right == nullptr) {
                    root = nullptr;
                }
                else {
                    root = root->Right;
                }
            }
            else if (root->Right == nullptr) {
                root = root->Left;
            }
            else {
                int value = root->Data;
                AVL_Node* node_right = root->Right;
                while (node_right->Left != nullptr) {
                    node_right = node_right->Left;
                }
                AVL_Node* node_left = root->Left;
                while (node_left->Right != nullptr) {
                    node_left = node_left->Right;
                }
                if (value - node_left->Data < node_right->Data - value) {
                    erase(root, pos + 1);
                    node_left->Left = root->Left;
                    node_left->Right = root->Right;
                    node_left->children = root->children;
                    root = node_left;
                }
                else {
                    erase(root, pos - 1);
                    node_right->Left = root->Left;
                    node_right->Right = root->Right;
                    node_right->children = root->children;
                    root = node_right;
                }
            }
            balance(root);
        }
    }
}

int main() {
    int n = 0, command = 0;
    std::cin >> n;
    int value = 0;
    AVL_Node *tree = nullptr;
    int result = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> command >> value;
        if (command == 1) {
            result = 0;
            insert(tree, value, result);
            std::cout << result << std::endl;
        }
        else {
            erase(tree, value);
        }
    }
    return 0;
}