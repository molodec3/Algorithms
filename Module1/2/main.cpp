#include <iostream>

struct point {
    int x;
    int y;
};

int count_square(point p1, point p2) {
    return (p2.x - p1.x) * (p2.y + p1.y);
}

int main() {
    int n;
    int square = 0;
    point start, first, second;
    std::cin >> n;
    std::cin >> start.x >> start.y;
    first.x = start.x;
    first.y = start.y;
    for (int i = 1; i < n; i++) {
        std::cin >> second.x >> second.y;
        square += count_square(first, second);
        first.x = second.x;
        first.y = second.y;
    }
    square += count_square(second, start);
    std::cout << (double)(square) / 2 << std::endl;
    return 0;
}