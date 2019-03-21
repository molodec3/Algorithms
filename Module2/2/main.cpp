#include <iostream>

class Heap {
public:
    Heap(std::pair<int, int>* segments, int n);
    ~Heap() {
        delete []buffer;
    }
    void sift_down(int position);
    void build();
    void sort();
    int count_result();
private:
    std::pair<int, int>* buffer;
    int real_size;
    int arr_size;
};

Heap::Heap(std::pair<int, int>* segments, int n) {
    buffer = segments;
    real_size = n - 1;
    arr_size = real_size;
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

void Heap::build() {
    for (int i = real_size / 2 ; i >= 0; --i) {
        sift_down(i);
    }
}

void Heap::sort() {
    while (real_size > 0) {
        std::swap(buffer[0], buffer[real_size]);
        --real_size;
        sift_down(0);
    }
}

int Heap::count_result() {
    int result = buffer[arr_size].second - buffer[arr_size].first;
    for (int i = arr_size - 1; i >= 0; --i) {
        if (buffer[i].second < buffer[i + 1].second) {
            buffer[i] = buffer[i + 1];
        }
        else {
            if (buffer[i].first < buffer[i + 1].second) {
                result += (buffer[i].second - buffer[i + 1].second);
            }
            else {
                result += (buffer[i].second - buffer[i].first);
            }
        }
    }
    return result;
}

int main() {
    int len;
    std::cin >> len;
    std::pair<int, int>* segments = new std::pair<int, int>[len];
    for (int i = 0; i < len; ++i) {
        std::cin >> segments[i].first >> segments[i].second;
    }
    Heap sorted_segments(segments, len);
    sorted_segments.build();
    sorted_segments.sort();
    std::cout << sorted_segments.count_result() << std::endl;
    return 0;
}