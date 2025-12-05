#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>

std::tuple<std::string, std::string> p05(const std::string &input) {
    int64_t ans1 = 0;
    int64_t ans2 = 0;

    std::vector<std::tuple<uint64_t,uint64_t>> ranges;
    std::vector<uint64_t> ingredients;

    {
        uint64_t num = 0;
        bool havenum = false;
        uint64_t first = 0;
        bool havefirst = false;
        for (const auto c: input) {
            if (c >= '0' && c <= '9') {
                num *= 10;
                num += c - '0';
                havenum = true;
            } else {
                if (c == '-') {
                    first = num;
                    havefirst = true;
                }
                else if (c == '\n') {
                    if (havenum) {
                        if (havefirst) {
                            ranges.emplace_back(first, num);
                        } else {
                            ingredients.emplace_back(num);
                        }
                    }
                    havefirst = false;
                }
                havenum = false;
                num = 0;
            }
        }

    }

    for (auto i : ingredients) {
        for (auto [b,e]: ranges) {
            if (i >= b && i <= e) { ans1++; break;}
        }
    }

    std::vector<std::tuple<uint64_t,int>> points;
    for (auto [b,e]: ranges) {
        points.emplace_back(b, 1);
        points.emplace_back(e, -1);
    }

    std::sort(points.begin(), points.end(), [](auto & a, auto & b) {
        auto[as,ad] = a;
        auto[bs,bd] = b;
        if (as == bs) return ad > bd;
        return as < bs;
    });

    ans2 = 0;
    int level = 0;
    uint64_t start = 0;

    for (auto [current,b] : points) {
        if (b>0) {
            if (level == 0) {
                start = current;
            }
            level+=b;
        }
        else if (b<0){
            level--;
            if (level == 0) {
                ans2 += (current-start+1);
            }
        }
    }

    return {std::to_string(ans1), std::to_string(ans2)};
}