#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>
#include <map>

std::tuple<std::string, std::string> p22(const std::string &input) {
    int64_t ans1 = 0;
    int64_t ans2 = 0;
    std::vector<int64_t> nums;
    {
        int64_t num = 0;
        bool havenum = false;
        for (const auto c: input) {
            if (c >= '0' && c <= '9') {
                num *= 10;
                num += c - '0';
                havenum = true;
            } else {
                if (havenum) {
                    nums.push_back(num);
                }
                havenum = false;
                num = 0;
            }
        }

    }

    auto iterate = [](int64_t i) {
        i = ((i*64)^i) % (1<<24);
        i = ((i/32)^i) % (1<<24);
        i = ((i*2048)^i) % (1<<24);
        return i;
    };

    std::map<std::tuple<int,int,int,int>, int> price;
    for (auto num : nums) {
        int p0 = num % 10;
        num = iterate(num);
        int p1 = num % 10;
        num = iterate(num);
        int p2 = num % 10;
        num = iterate(num);
        int p3 = num % 10;
        int d0 = p1-p0;
        int d1 = p2-p1;
        int d2 = p3-p2;
        std::set<std::tuple<int,int,int,int>> seen_set;
        for (int i = 3; i < 2000; i++) {
            num = iterate(num);
            int p4 = num % 10;
            int d3 = p4-p3;
            auto tup = std::make_tuple(d0,d1,d2,d3);
            if (seen_set.find(tup) == seen_set.end()) {
                price[tup] += p4;
            }
            seen_set.insert(tup);
            d0 = d1;
            d1 = d2;
            d2 = d3;
            p3 = p4;
        }
        ans1 += num;
    }

    for (auto & [k,v] : price) {
        if (v > ans2) ans2 = v;
    }

    return {std::to_string(ans1), std::to_string(ans2)};
}
