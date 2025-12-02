#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>

std::tuple<std::string, std::string> p02(const std::string &input) {
    uint64_t ans1 = 0;
    uint64_t ans2 = 0;

    std::vector<std::tuple<uint64_t, uint64_t>> v;

    {
        uint64_t num = 0;
        uint64_t num1 = 0;
        bool havenum = false;
        for (const auto c: input) {
            if (c >= '0' && c <= '9') {
                num *= 10;
                num += c - '0';
                havenum = true;
            } else {
                if (c=='-') {
                    num1 = num;
                } else if (havenum) {
                    v.emplace_back(num1, num);
                }
                havenum = false;
                num = 0;
            }
        }

    }

    for (auto [n1,n2] : v) {
        for (auto i = n1; i <= n2; i++) {
            auto s = std::to_string(i);
            auto l = s.length();
            if (s.substr(0,l/2) == s.substr(l/2)) {
                ans1 += i;
                ans2 += i;
                continue;
            }

            for (size_t j = 1; j <= l/2; j++) {
                if (l % j) continue;
                auto ss = s.substr(0, j);
                bool ok = true;
                for (auto p = j; p < l; p+= j) {
                    if (ss != s.substr(p,j)) {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    ans2 += i;
                    break;
                }
            }

        }
    }

    return {std::to_string(ans1), std::to_string(ans2)};
}
