#include <iostream>
#include <vector>


void median (int* sequence, int left, int right) {
    int mid = (left + right) / 2;
    if (sequence[right] < sequence[mid]) {
        std::swap(sequence[right], sequence[mid]);
    }
    if (sequence[left] < sequence[mid]) {
        std::swap(sequence[left], sequence[mid]);
    }
    if (sequence[right] < sequence[left]) {
        std::swap(sequence[right], sequence[left]);
    }
}

int partition (int* sequence, int left, int right) {
    median(sequence, left, right);
    int pivot = sequence[left];
    int j = right, i = right;
    for ( ; j > left; --j) {
        if (sequence[j] > pivot) {
            std::swap(sequence[j], sequence[i--]);
        }
    }
    std::swap(sequence[left], sequence[i]);
    return (i);
}

int k_stat (int* sequence, int left, int right, int k) {
    int part = partition(sequence, left, right);
    while (part != k) {
        if (part < k) {
            left = part + 1;
            part = partition(sequence, left, right);
        }
        else {
            right = part;
            part = partition(sequence, left, right);
        }
    }
    return sequence[k];
}

int main() {
    int n = 0, k = 0;
    std::cin >> n >> k;
    int* sequence = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> sequence[i];
    }
    std::cout << k_stat(sequence, 0, n - 1, k) << std::endl;
    delete[] sequence;
    return 0;
}