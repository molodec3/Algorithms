#include <iostream>
#include <vector>

void count_sort (std::vector<unsigned long long>& sequence, int n, long long pos) {
    int positions[10];
    for (int i = 0; i < 10; i++) {
        positions[i] = 0;
    }
    std::vector<unsigned long long> final_sequence(n);
    for (int i = 0; i < n; ++i) {
        ++positions[(sequence[i] / pos) % 10];
    }
    for (int i = 1; i < 10; ++i) {
        positions[i] += positions[i - 1];
    }
    for (int i = n - 1; i >= 0; --i) {
        final_sequence[(positions[(sequence[i] / pos) % 10]--) - 1] = sequence[i];
    }
    sequence = final_sequence;
}

void radix (std::vector<unsigned long long>& sequence, int n) {
    long long pos = 1;
    for (int i = 1; i <= 21; ++i) {
        count_sort(sequence, n, pos);
        pos *= 10;
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<unsigned long long> sequence(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> sequence[i];
    }
    radix(sequence, n);
    for (int i = 0; i < n; ++i) {
        std::cout << sequence[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}