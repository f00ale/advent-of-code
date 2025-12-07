#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>

std::tuple<std::string, std::string> p03(const std::string &input) {
    uint64_t ans1 = 0;
    uint64_t ans2 = 0;

    std::vector<std::vector<int>> v;

    {
        bool first = true;
        for (const auto c: input) {
            if (c >= '0' && c <= '9') {
                if (first) {
                    v.emplace_back();
                    first = false;
                }
                v.back().push_back(c - '0');
            } else {
                if (c == '\n') first = true;
            }
        }

    }

    for (auto p : {1,2}) {
        const size_t N = ((p == 1) ? 2 : 12);
        for (const auto &r: v) {
            auto dp = std::vector(r.size(), std::vector<uint64_t>(N,0));
            for (int i = r.size()-1; i >= 0; i--) {
                dp[i][0] = r[i];
            }
            uint64_t mul = 1;
            for (size_t n = 1; n < N; n++) {
                mul *= 10;
                for (int i = r.size()-1; i >= 0; i--) {
                    uint64_t tmp = r[i] * mul;
                    for (size_t j = i+1; j < r.size(); j++) {
                        if (!dp[j][n-1]) continue;
                        if (tmp + dp[j][n-1] > dp[i][n]) dp[i][n] = tmp + dp[j][n-1];
                    }
                }
            }

            uint64_t m = 0;
            for (const auto & k : dp) {
                if (k.back() > m) m = k.back();
            }
            ((p == 1) ? ans1 : ans2) += m;
        }
    }
    return {std::to_string(ans1), std::to_string(ans2)};
}
