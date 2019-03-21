#include <iostream>
#include <vector>

long long count_pyr (int n,
        std::vector<std::vector<long long> > dp) {
    dp[0].push_back(1);
    for (int i = 1; i < n; ++i) {
        int j = i;
        dp[i].resize(i + 1);
        dp[i][j--] = 1;
        while (j >= 0) {
            i - j - 1 >= j ? dp[i][j] = dp[i][j + 1] + dp[i - j - 1][j] : dp[i][j] = dp[i][j + 1];
            --j;
        }
    }
    return dp[n - 1][0];
}

int main() {
    int n = 0;
    std::cin >> n;
    std::vector<std::vector<long long> > dp(n);
    std::cout << count_pyr(n, dp);
    return 0;
}