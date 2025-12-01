#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>

std::tuple<std::string, std::string> p01(const std::string &input) {
    int64_t ans1 = 0;
    int64_t ans2 = 0;
    std::vector<int> v;
    {
        int num = 0;
        bool havenum = false;
        bool neg = false;
        for (const auto c: input) {
            if (c >= '0' && c <= '9') {
                num *= 10;
                num += c - '0';
                havenum = true;
            } else if (c == 'R') {
                neg = false;
            } else if (c == 'L') {
                neg = true;
            } else if (c == '\n') {
                if (havenum) {
                    v.push_back((neg ? -1 : 1)*num);
                }

                havenum = false;
                num = 0;
            }
        }

    }

    int pos = 50;
    for (auto r : v) {
        if (r > 0) {
            pos += r;
            while (pos >= 100) {
                pos -= 100;
                ans2++;
            }
            if (pos == 0) ans1++;
        } else if (r < 0) {
            if (pos == 0) ans2--;
            pos += r;
            while (pos < 0) {
                pos += 100;
                ans2++;
            }
            if (pos == 0) ans1++, ans2++;
        }
    }

    return {std::to_string(ans1), std::to_string(ans2)};
}
