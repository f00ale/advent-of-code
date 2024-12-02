#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <map>

std::tuple<std::string, std::string> p01(const std::string &input) {
    int64_t ans1 = 0;
    int64_t ans2 = 0;
    std::vector<int> v1, v2;
    {
        int num = 0;
        bool havenum = false;
        bool first = true;
        for (const auto c: input) {
            if (c >= '0' && c <= '9') {
                num *= 10;
                num += c - '0';
                havenum = true;
            } else {
                if (havenum) {
                    (first ? v1 : v2).push_back(num);
                    first = !first;
                }
                havenum = false;
                num = 0;
            }
        }

    }

    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());
    for (size_t i = 0; i < v1.size(); i++) {
        ans1 += abs(v1[i] - v2[i]);
    }

    std::map<int,int> c1, c2;
    for (auto i : v1) { c1[i]++; }
    for (auto i : v2) { c2[i]++; }
    for (auto [n,c] : c1) {
        ans2 += c * n * c2[n];
    }
    return {std::to_string(ans1), std::to_string(ans2)};
}
