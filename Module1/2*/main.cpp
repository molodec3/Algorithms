/*Дан массив целых чисел A[0..n). Массив произвольным образом
 * заполнен натуральными числами из диапазона [0..n - 1). Одно или
 * несколько значений в массиве может повторяться. Необходимо найти
 * любой повтор за O(n), памяти O(1). Исходный массив хранить можно,
 * модифицировать нельзя.
n ≤ 10000.*/



#include <iostream>

int find_c(int* numbers, int f_pointer, int s_pointer, int n, int len) {
    for (int i = 0; i < n - len; i++) {
        if (numbers[f_pointer] == numbers[s_pointer]) {
            return numbers[s_pointer];
        }
        else {
            f_pointer = numbers[f_pointer];
            s_pointer = numbers[s_pointer];
        }
    }
}

int main() {
    int n;
    std::cin >> n;
    int *numbers = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        std::cin >> numbers[i];
    }
    int position = n - 1;
    for (int i = 0; i < n; i++) {
        position = numbers[position];
    }
    int pointer_c = position, len = 1; //pointer_c - указывает на цикл, len - длина цикла
    position = numbers[position];
    while (position != pointer_c) {
        len += 1;
        position = numbers[position];
    }
    position = n - 1;
    for (int i = 0; i < len; i++) {
        position = numbers[position];
    }
    std::cout << find_c(numbers, position, n - 1, n, len) << std::endl;
    free(numbers);
    return 0;
}