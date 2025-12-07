#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>

std::tuple<std::string, std::string> p07(const std::string &input) {
    uint64_t ans1 = 0;
    uint64_t ans2 = 0;
    std::vector<std::string> v;
    {
        bool first = true;
        for (const auto c: input) {
            if (c == '.' || c == '^' || c == 'S') {
                if (first) {
                    first = false;
                    v.emplace_back();
                }
                v.back().push_back(c);
            } else if (c == '\n') {
                first = true;
            }
        }

    }
    std::vector ways(v.size(), std::vector(v.back().size(), 0ull));
    for (size_t i = 0; i < v[0].size(); ++i) {
        if (v[0][i] == 'S') { ways[0][i] = 1; }
    }
    for (size_t i = 1; i < v.size(); ++i) {
        for (size_t j = 0; j < v[i].size(); ++j) {
            if (v[i][j] == '.') {
                ways[i][j] += ways[i - 1][j];
            } else if (v[i][j] == '^') {
                if (ways[i-1][j]) ans1 += 1;
                ways[i][j-1] += ways[i - 1][j];
                ways[i][j+1] += ways[i - 1][j];
            }
        }
    }

    for (auto i : ways.back()) {
        ans2 += i;
    }

    return {std::to_string(ans1), std::to_string(ans2)};
}
