/* Для сложения чисел используется старый компьютер. Время,
 * затрачиваемое на нахождение суммы двух чисел равно их
 * сумме. Таким образом для нахождения суммы чисел 1,2,3 может
 * потребоваться разное время, в зависимости от порядка вычислений.
 * ((1+2)+3) -> 1+2 + 3+3 = 9 ((1+3)+2) -> 1+3 + 4+2 = 10 ((2+3)+1)
 * -> 2+3 + 5+1 = 11 Требуется написать программу, которая
 * определяет минимальное время, достаточное для вычисления
 * суммы заданного набора чисел.*/


#include <iostream>

int maxi(int a, int b) {
    return (a >= b) ? a : b;
}

class Heap {
public:
    Heap(int* numbers, int n) : buffer_size(n), buffer (numbers), real_size(n) {}
    ~Heap();
    int extract_root();
    void sift_down(int position);
    void sift_up(int position);
    void insert(int value);
    void build();
    int size() {return real_size;}
    void out();
private:
    int buffer_size;
    int* buffer;
    int real_size;
};

Heap::~Heap() {
    buffer = new int[0];
}

void Heap::sift_down(int position) {
    while (2 * position + 1 <= real_size) {
        int right = 2 * position + 2;
        int left = 2 * position + 1;
        int lowest = position;
        if (buffer[left] < buffer[position]) {
            lowest = left;
        }
        if (right <= real_size && buffer[right] < buffer[lowest]) {
            lowest = right;
        }
        if (lowest != position) {
            std::swap(buffer[position], buffer[lowest]);
            position = lowest;
        }
        else {
            break;
        }
    }
}

void Heap::sift_up(int position) {
    while (buffer[position] < buffer[(position - 1) / 2] && position > 0) {
        std::swap(buffer[position], buffer[(position - 1) / 2]);
        position = (position - 1) / 2;
    }
}

void Heap::out() {
    for (int i = 0; i <= real_size; ++i)
        std::cout << buffer[i] << " ";
}

int Heap::extract_root() {
    if (real_size > -1) {
        int result = buffer[0];
        buffer[0] = buffer[real_size--];
        if (real_size > -1) {
            sift_down(0);
        }
        return result;
    }
    return 0;
}

void Heap::build() {
    for (int i = real_size / 2 ; i >= 0; --i) {
        sift_down(i);
    }
}

void Heap::insert(int value) {
    if (real_size == buffer_size) {
        int new_size = maxi(2 * buffer_size, 1);
        int* new_buffer = new int[new_size];
        for (int i = 0; i < real_size; ++i) {
            new_buffer[i] = buffer[i];
        }
        buffer = new_buffer;
        buffer_size = new_size;
        delete[](new_buffer);
    }
    buffer[++real_size] = value;
    sift_up(real_size);
}

int main() {
    int n = 0, sum = 0;
    std::cin >> n;
    int* numbers = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> numbers[i];
    }
    Heap heap_num(numbers, n - 1);
    heap_num.build();
    int answer = 0;
    while (heap_num.size() >= 0) {
        if (sum > 0) {
            heap_num.insert(sum);
            sum = 0;
        }
        int min_a = 0, min_b = 0;
        min_a = heap_num.extract_root();
        min_b = heap_num.extract_root();
        sum = min_a + min_b;
        answer += sum;
    }
    delete[](numbers);
    heap_num.~Heap();
    std::cout << answer << std::endl;
    return 0;
}