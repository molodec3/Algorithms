#include <iostream>
#include <vector>

void max(int& a, int& b) {
    if (a > b) std::swap(a, b);
}

void count_subtree_dist (std::vector<std::vector<int> >& tree, int subtree_index,
        std::vector<int>& subtree_size, std::vector<int>& subtree_dist_sum) {
    std::vector<int> subtree = tree[subtree_index];
    for (int i = 0; i < subtree.size(); ++i) {
        count_subtree_dist(tree, subtree[i], subtree_size, subtree_dist_sum);
        subtree_size[subtree_index] += subtree_size[subtree[i]];
        subtree_dist_sum[subtree_index] += (subtree_dist_sum[subtree[i]] + subtree_size[subtree[i]]);
    }
    ++subtree_size[subtree_index];
}

int main() {
    int n = 0;
    std::cin >> n;
    int v1 = 0, v2 = 0;
    std::vector<std::vector<int> > tree(n);
    std::vector<int> parents(n);
    for (int i = 0; i < n - 1; ++i) {
        std::cin >> v1 >> v2;
        max(v1, v2);
        tree[v1].push_back(v2);
        parents[v2] = v1;
    }
    std::vector<int> subtree_size(n);
    std::vector<int> subtree_dist_sum(n);
    count_subtree_dist(tree, 0, subtree_size, subtree_dist_sum);
    std::cout << subtree_dist_sum[0] << std::endl;
    for (int i = 1; i < n; ++i) {
        subtree_dist_sum[i] = n - 2 * subtree_size[i] + subtree_dist_sum[parents[i]];
        std::cout << subtree_dist_sum[i] << std::endl;
    }
    return 0;
}