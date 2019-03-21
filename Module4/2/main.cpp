#include <iostream>
#include <vector>
#include <algorithm>

int count_height (std::vector<std::pair<int, int> >const& athletes) {
    int c_mas = athletes[0].first;
    int height = 1;
    for (int i = 1; i < athletes.size(); ++i) {
        if (athletes[i].second >= c_mas) {
            ++height;
            c_mas += athletes[i].first;
        }
    }
    return height;
}

int main() {
    std::vector<std::pair<int, int> > athletes;
    int si = 0, mi = 0;
    while (std::cin >> mi >> si) {
        athletes.push_back(std::make_pair(mi, si));
    }
    std::sort(athletes.begin(), athletes.end());
    std::cout << count_height(athletes) << std::endl;
    return 0;
}