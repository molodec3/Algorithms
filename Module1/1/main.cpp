#include <iostream>
#include <cmath>

int max_divisor(int n) {
    int m = sqrt(n) + 2;
    for (int i = 2; i < m ; i++) {
        if (n % i == 0) return n / i;
    }
    return 1;
}

int main() {
    int n;
    std::cin >> n;
    int div = max_divisor(n);
    std::cout << div << " " << n - div << std::endl;
    return 0;
}
