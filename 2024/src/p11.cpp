#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <map>

std::tuple<std::string, std::string> p11(const std::string &input) {
    int64_t ans1 = 0;
    int64_t ans2 = 0;

    std::vector<uint64_t> v;
    {
        int num = 0;
        bool havenum = false;
        for (const auto c: input) {
            if (c >= '0' && c <= '9') {
                num *= 10;
                num += c - '0';
                havenum = true;
            } else {
                if (havenum) v.push_back(num);
                havenum = false;
                num = 0;
            }
        }

    }

    std::map<uint64_t, uint64_t> map;
    for (auto num: v) map[num]++;
    for (int i = 0; i < 75; i++) {
        if (i==25) for (auto [n,ant]: map) ans1 += ant;
        std::map<uint64_t, uint64_t> next;
        for (auto [n, ant] : map) {
            auto s = std::to_string(n);
            if ( n == 0) {
                next[1]+=ant;
            } else if (s.size() % 2 == 0) {
                auto s1 = s.substr(0, s.size() / 2);
                auto s2 = s.substr(s.size() / 2);
                next[std::stoull(s1)]+=ant;
                next[std::stoull(s2)]+=ant;
            } else {
                next[n*2024]+=ant;
            }

        }
        map.swap(next);
    }

    for (auto [n,ant]: map) ans2 += ant;

    return {std::to_string(ans1), std::to_string(ans2)};
}
