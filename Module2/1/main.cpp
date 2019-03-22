#include <iostream>

struct Point {
    int x;
    int y;
};


void Insertion(Point* points, int len) {
    for (int i = 1; i < len; ++i) {
        Point temp = points[i];
        int j = i - 1;
        for ( ; j >= 0 && temp.x < points[j].x; --j) {
            points[j + 1] = points[j];
        }
        while (temp.y < points[j].y && temp.x == points[j].x) {
            points[j + 1] = points[j];
            --j;
        }
        points[j + 1] = temp;
    }
}

int main() {
    int n = 0;
    std::cin >> n;
    Point* points = new Point[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> points[i].x >> points[i].y;
    }
    Insertion(points, n);
    for (int i = 0; i < n; ++i) {
        std::cout << points[i].x << " " << points[i].y << std::endl;
    }
    delete[] points;
    return 0;
}