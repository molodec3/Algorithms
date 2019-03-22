#include <iostream>
#include <vector>

class Heap {
public:
    Heap(std::vector< std::vector<int> > numbers, int k) : size(k - 1), buffer (numbers) {}
    void sift_down(int position);
    void build();
    int k_size() {return size + 1;}
    int front();
private:
    int size;
    std::vector< std::vector<int> > buffer;
};

void Heap::sift_down(int position) {
    while (2 * position + 1 <= size) {
        int right = 2 * position + 2;
        int left = 2 * position + 1;
        int lowest = position;
        if (buffer[left][buffer[left][0]] < buffer[position][buffer[position][0]]) {
            lowest = left;
        }
        if (right <= size && buffer[right][buffer[right][0]] < buffer[lowest][buffer[lowest][0]]) {
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
    for (int i = size / 2; i >= 0; --i) {
        sift_down(i);
    }
}

int Heap::front() {
    int result = buffer[0][buffer[0][0]++];
    if (buffer[0].size() == buffer[0][0]) {
        buffer[0] = buffer[size--];
    }
    return result;
}

void merge(Heap& in_heap) {
    while (in_heap.k_size() != 0) {
        std::cout << in_heap.front() << " ";
        if (in_heap.k_size() == 0)  {
            break;
        }
        in_heap.sift_down(0);
    }
}


int main() {
    int n = 0, k = 0;
    std::cin >> n >> k;
    std::vector< std::vector<int> > sequence(k);
    for (int i = 0; i < k; ++i) {
        sequence[i].push_back(1);
    }
    for (int i = 0; i < n; ++i) {
        int element = 0;
        std::cin >> element;
        sequence[i % k].push_back(element);
    }
    Heap k_sequence(sequence, k);
    k_sequence.build();
    merge(k_sequence);
    std::cout << std::endl;
    return 0;
}