#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>

uint64_t concat(uint64_t a, uint64_t b) {
    return std::stoull(std::to_string(a)+std::to_string(b));
}

int rec(uint64_t target, uint64_t curr, std::vector<uint64_t>::iterator it, std::vector<uint64_t>::iterator end) {
    if (it == end) {
        return target == curr;
    }
    return rec(target, curr + *it, it+1, end) + rec(target, curr * *it, it+1, end);
}
int rec2(uint64_t target, uint64_t curr, std::vector<uint64_t>::iterator it, std::vector<uint64_t>::iterator end) {
    if (it == end) {
        return target == curr;
    }
    return rec2(target, curr + *it, it+1, end) +
           rec2(target, curr * *it, it+1, end) +
               rec2(target, concat(curr,*it), it+1, end);
}

std::tuple<std::string, std::string> p07(const std::string &input) {
    int64_t ans1 = 0;
    int64_t ans2 = 0;
    std::vector<std::vector<uint64_t>> vs;
    {
        uint64_t num = 0;
        bool havenum = false;
        bool first = true;
        for (const auto c: input) {
            if (c >= '0' && c <= '9') {
                num *= 10;
                num += c - '0';
                havenum = true;
            } else {
                if (havenum) {
                    if (first) {  vs.emplace_back(); first = false; }
                    vs.back().push_back(num);
                }
                if (c == '\n') first = true;
                havenum = false;
                num = 0;
            }
        }

    }

    for (auto &v: vs) {
        if (rec(v[0], v[1], v.begin()+2, v.end())) ans1 += v[0];
        if (rec2(v[0], v[1], v.begin()+2, v.end())) ans2 += v[0];
    }

    return {std::to_string(ans1), std::to_string(ans2)};
}
