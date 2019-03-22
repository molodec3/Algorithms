/*Дана последовательность N прямоугольников
 * различной ширины и высоты (wi, hi).
 * Прямоугольники расположены, начиная с
 * точки (0, 0), на оси ОХ вплотную друг за
 * другом (вправо).
Требуется найти M - площадь максимального
 прямоугольника (параллельного осям координат),
 который можно вырезать из этой фигуры.

Время работы - O(n).*/

#include <iostream>
#include <malloc.h>

class Stack {
public:
    Stack(int Size);
    ~Stack();
    void Push(int value);
    int Pop();
    bool IsEmpty();

private:
    int* buffer;
    int buffer_Size;
    int top;
};

Stack::Stack(int Size) : buffer(new int[Size]), buffer_Size(Size), top(-1) {}

Stack::~Stack() {
    buffer = new int[0];
}

void Stack::Push(int value) {
    buffer[++top] = value;
}

bool Stack::IsEmpty() {
    return (top == -1);
}

int Stack::Pop() {
    if (top == -1) {
        return -1;
    }
    else {
        return buffer[top--];
    }
}


int find_max_sq(int* x_coord, int* y_coord, int n) {
    Stack Rectangles_x(n), Rectangles_y(n);//, Rectangles_xbegin(n);
    int max_square = 0, sum_x = 0;
    Rectangles_x.Push(x_coord[0]);
    Rectangles_y.Push(y_coord[0]);
    for (int i = 1; i < n; i++) {
        if (y_coord[i] > y_coord[i - 1]) {
            Rectangles_x.Push(x_coord[i]);
            Rectangles_y.Push(y_coord[i]);
        }
        else {
            sum_x = 0;
            int last_x = x_coord[i], last_y = y_coord[i];
            int current_x = Rectangles_x.Pop(), current_y = Rectangles_y.Pop();
            while (last_y <= current_y) {
                sum_x += current_x;
                if (sum_x * current_y > max_square) {
                    max_square = sum_x * current_y;
                }
                current_x = Rectangles_x.Pop();
                current_y = Rectangles_y.Pop();
            }
            Rectangles_x.Push(current_x); //положить обратно, что достали на пред шаге
            Rectangles_y.Push(current_y); //но не использовали
            sum_x += last_x;
            if (sum_x * last_y > max_square) {
                max_square = sum_x * last_y;
            }
            Rectangles_x.Push(sum_x);
            Rectangles_y.Push(last_y);
        }
    }
    Rectangles_x.~Stack();
    Rectangles_y.~Stack();
    return max_square;
}


int main() {
    int n;
    std::cin >> n;
    int *x_coord = (int*)malloc((n + 1) * sizeof(int));
    int *y_coord = (int*)malloc((n + 1) * sizeof(int));
    for (int i = 0; i < n; i++) {
        std::cin >> x_coord[i] >> y_coord[i];
    }
    x_coord[n] = 0;
    y_coord[n] = 0;
    std::cout << find_max_sq(x_coord, y_coord, n + 1) << std::endl;
    return 0;
}