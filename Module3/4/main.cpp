#include <iostream>
#include <queue>
#include <vector>
#include "Huffman.h"

typedef unsigned char byte;

struct Node {
    int Data;
    int frequency;
    Node* Left;
    Node* Right;
    Node() : Data(-1), frequency(0), Left(nullptr), Right(nullptr) {}
};

struct cmp {
    bool operator()(Node*& a, Node*& b) {
        return a->frequency > b->frequency;
    }
};

Node* make_node(Node*& a, Node*& b) {
    Node* root = new Node();
    root->Left = a;
    root->Right = b;
    root->frequency = a->frequency + b->frequency;
    return root;
}

Node* make_tree(std::priority_queue<Node*, std::vector<Node*>, cmp> q) {
    while (!q.empty()) {
        Node* first_element = q.top();
        q.pop();
        if (!q.empty()) {
            Node* element = q.top();
            q.pop();
            q.push(make_node(first_element, element));
        }
        else {
            return first_element;
        }
    }
}

void dfs(Node* root, int seq, std::vector<int>& code) {
    if (root->Right == nullptr && root->Left == nullptr) {
        code[root->Data] = seq;
        return;
    }
    dfs(root->Left, 2 * seq, code);
    dfs(root->Right, 2 * seq + 1, code);
}

Node* root = nullptr;
int n = 0;

int reverse (int value) {
    if (value == 0) return 0;
    int res = 1;
    while (!(value % 2 == 1 && value / 2 == 0)) {
        if (value % 2 == 0) {
            res *= 2;
        }
        else {
            res = res * 2 + 1;
        }
        value /= 2;
    }
    return res;
}

static void copyStream(IInputStream& input, IOutputStream& output)
{
    byte value;
    while (input.Read(value))
    {
        output.Write(value);
    }
}

void Encode(IInputStream& original, IOutputStream& compressed) {
    std::priority_queue<Node*, std::vector<Node*>, cmp> q;
    byte value;
    std::vector<int> symbols(256);
    std::vector<byte> message;
    std::vector<int> code(256);
    while (original.Read(value)) {
        ++symbols[value];
        message.push_back(value);
    }
    n = message.size();
    for (int i = 0; i < 256; ++i) {
        if (symbols[i] > 0) {
            Node *c_node = new Node();
            c_node->Data = i;
            c_node->frequency = symbols[i];
            q.push(c_node);
        }
    }
    root = make_tree(q);
    dfs(root, 1, code);
    if (root->Data >= 0) {
        for (int i = 0; i < message.size(); ++i) {
            compressed.Write(message[i]);
        }
    }
    else {
        int i = 0;
        int code_m = reverse(code[message[i]]); //код текущего символа на вводе
        while (i < message.size()) {
            int c_code = 1; //текущий код, который будет выведен
            for (int j = 0; j < 8; ++j) {
                if (code_m == 1) {
                    code_m = reverse(code[message[++i]]);
                }
                if (code_m % 2 == 0) {
                    c_code *= 2;
                } else {
                    c_code = c_code * 2 + 1;
                }
                code_m /= 2;
            }
            compressed.Write(c_code & 255);
        }
    }
}

void Decode(IInputStream& compressed, IOutputStream& original) {
    byte c_code[8];
    byte value;
    std::vector<int> code(256);
    dfs(root, 1, code);
    Node* node = root;
    int c_n = 0;
    int j = 0;
    if (root->Data >= 0) {
        copyStream(compressed, original);
    }
    else {
        while (compressed.Read(value)) {
            for (int i = 7; i >= 0; --i) {
                c_code[i] = value % 2;
                value /= 2;
            }
            while (c_n < n) {
                if (node->Data < 0) {
                    if (c_code[j] == 0) {
                        node = node->Left;
                    } else {
                        node = node->Right;
                    }
                    ++j;
                }
                if (node->Data >= 0) {
                    original.Write(node->Data);
                    ++c_n;
                    node = root;
                }
                if (j >= 8) {
                    j = 0;
                    break;
                }
            }
        }
    }
}
