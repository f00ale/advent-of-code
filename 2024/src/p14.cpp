#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>

std::tuple<std::string, std::string> p14(const std::string &input) {
    int64_t ans1 = 0;
    int64_t ans2 = 0;
    std::vector<std::tuple<int, int, int, int>> robots;
    {
        int num = 0;
        bool havenum = false;
        bool neg = false;
        std::vector<int> tmp;
        for (const auto c: input) {
            if (c >= '0' && c <= '9') {
                num *= 10;
                num += c - '0';
                havenum = true;
            } else if (c == '-') {
                neg = true;
            } else {
                if (havenum) {
                    if (neg) num = -num;
                    tmp.push_back(num);
                    if (tmp.size() == 4) {
                        robots.emplace_back(tmp[0], tmp[1], tmp[2], tmp[3]);
                        tmp.clear();
                    }
                }
                neg = false;
                havenum = false;
                num = 0;
            }
        }

    }
    constexpr int SX = 101, SY = 103;
    bool found = false;
    std::vector<std::vector<int>> field(SY, std::vector<int>(SX, 0));

    for (int t = 1; t<=100 || !found; t++) {
        for (auto & [px,py,vx,vy]: robots) {
            px += vx;
            py += vy;
            if (px < 0) px += SX;
            if (px >= SX) px -= SX;
            if (py < 0) py += SY;
            if (py >= SY) py -= SY;
            field[py][px] = t;
        }
        for (auto & v : field) {
            int ant = 0;
            for (auto i : v) {
                if (i == t) {
                    ant++;
                    if (ant > 20) found = true;
                } else ant = 0;
            }
        }
        if (found) ans2 = t;
        if (t == 100) {
            int64_t q1, q2, q3, q4;
            q1 = q2 = q3 = q4 = 0;
            for (const auto [px,py,vx,vy]: robots) {
                if (px < SX/2) {
                    if (py < SY/2) q1++;
                    if (py > SY/2) q2++;
                }
                if (px > SX/2) {
                    if (py < SY/2) q3++;
                    if (py > SY/2) q4++;
                }
            }
            ans1 = q1*q2*q3*q4;
        }
    }

    return {std::to_string(ans1), std::to_string(ans2)};
}
