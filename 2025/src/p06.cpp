#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>

std::tuple<std::string, std::string> p06(const std::string &input) {
    uint64_t ans1 = 0;
    uint64_t ans2 = 0;

    std::vector<std::vector<uint64_t>> nums;
    std::string ops;
    std::vector<std::string> lines;
    {
        uint64_t num = 0;
        bool havenum = false;
        bool first = true;
        bool first2 = true;
        for (const auto c: input) {
            if (c=='\n') first2 = true;
            else {
                if (first2) {lines.emplace_back(); first2 = false;}
                lines.back().push_back(c);
            }
            if (c >= '0' && c <= '9') {
                num *= 10;
                num += c - '0';
                havenum = true;
            } else {
                if (havenum) {
                    if (first) {nums.emplace_back();}
                    first = false;
                    nums.back().emplace_back(num);
                    havenum = false;
                    num = 0;
                }
                if (c == '\n') first = true;
                else if (c == '+' || c == '*') {
                    ops.push_back(c);
                }
            }
        }
    }
    for (size_t i = 0; i < ops.size(); ++i) {
        char c = ops[i];
        uint64_t tmp = (c=='+' ? 0 : 1);
        for (const auto & v : nums) {
            if (c == '+') {
                tmp += v[i];
            } else {
                tmp *= v[i];
            }
        }
        ans1 += tmp;
    }

    size_t ll = 0;
    for (auto & l : lines) {
        ll = std::max(ll, l.size());
    }
    for (auto & l : lines) {
        while (l.size() < ll) {l.push_back(' ');}
    }

    char op = ' ';
    uint64_t tmp = 0;
    for (size_t i = 0; i < ll; ++i) {
        if (lines.back()[i] != ' ') {
            op = lines.back()[i];
            ans2 += tmp;
            tmp = (op == '+' ? 0 : 1);
        }
        uint64_t num = 0;
        bool numseen = false;
        for (size_t l = 0; l < lines.size()-1; ++l) {
            char c = lines[l][i];
            if (c >= '0' && c <= '9') {
                num *= 10;
                num += c - '0';
                numseen = true;
            }
        }
        if (! numseen) {
            ans2 += tmp;
            tmp = 0;
        }
        if (op == '+') {
            tmp += num;
        } else {
            tmp *= num;
        }

    }
    ans2 += tmp;

    return {std::to_string(ans1), std::to_string(ans2)};
}
