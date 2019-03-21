/*Дан массив целых чисел А[0..n-1]. Известно, что
 * на интервале [0, m] значения массива строго
 * возрастают, а на интервале [m, n-1] строго убывают
 * . Найти m за O(log m).
2 ≤ n ≤ 10000.*/

#include <iostream>
#include <malloc.h>

int b_search(int *numbers, int n, int l, int r) {
    while (r - l > 1) {
        int mid = (l + r) / 2;
        if (numbers[mid] < numbers[mid + 1]) {
            l = mid;
        }
        else {
            r = mid;
        }
    }
    return r;
}

int find_range(int *numbers, int n) {
    int current_pos = 1;
    while (2 * current_pos <= n) {
        if (numbers[current_pos] > numbers[current_pos - 1] &&
        numbers[2 * current_pos] < numbers[2 * current_pos - 1]) {
            return b_search(numbers, n, current_pos, current_pos * 2);
        }
        else {
            current_pos *= 2;
        }
    }
}


int main() {
    int n;
    std::cin >> n;
    int *numbers = (int*)malloc((n + 1) * sizeof(int));
    for (int i = 0; i < n; i++) {
        std::cin >> numbers[i];
    }
    numbers[n] = -1;
    std::cout << find_range(numbers, n);
    free(numbers);
    return 0;
}