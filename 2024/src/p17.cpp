#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>
#include <sstream>
#include <queue>

std::tuple<std::string, std::string> p17(const std::string &input) {
    std::string ans1;
    uint64_t ans2 = 0;
    std::vector<uint64_t> data;
    {
        uint64_t num = 0;
        bool havenum = false;
        for (const auto c: input) {
            if (c >= '0' && c <= '9') {
                num *= 10;
                num += c - '0';
                havenum = true;
            } else {
                if(havenum) data.push_back(num);
                havenum = false;
                num = 0;
            }
        }

    }
    const std::vector<int> cmds(data.begin()+3, data.end());

    auto solve = [] (const std::vector<int> & cmds, uint64_t a, uint64_t b, uint64_t c) {
        std::vector<int> output;
        auto combo = [&](uint64_t arg) {
            switch (arg) {
                case 0:
                case 1:
                case 2:
                case 3:
                    return arg;
                case 4:
                    return a;
                case 5:
                    return b;
                case 6:
                    return c;
                default:
                    std::cout << "invalid combo " << arg << std::endl;
                    return arg ^ arg;
            }
        };

        auto adv = [&](uint64_t arg) { a = a >> combo(arg); }; // 0
        auto bxl = [&](uint64_t arg) { b = (b ^ arg); }; // 1
        auto bst = [&](uint64_t arg) { b = combo(arg) & 0b111; }; // 2
        auto bxc = [&](uint64_t arg) { b = (b ^ c); }; // 4
        auto out = [&](uint64_t arg) { output.push_back(combo(arg) & 0b111); }; // 5
        auto bdv = [&](uint64_t arg) { b = a >> combo(arg); }; // 6
        auto cdv = [&](uint64_t arg) { c = a >> combo(arg); }; // 7

        size_t idx = 0;
        while (idx < cmds.size()) {
            auto next = idx + 2;

            switch (cmds[idx]) {
                case 0:
                    adv(cmds[idx + 1]);
                    break;
                case 1:
                    bxl(cmds[idx + 1]);
                    break;
                case 2:
                    bst(cmds[idx + 1]);
                    break;
                case 3:
                    if (a) next = cmds[idx + 1];
                    break; //jnz(cmds[idx+1]); break;
                case 4:
                    bxc(cmds[idx + 1]);
                    break;
                case 5:
                    out(cmds[idx + 1]); /* for (auto i : output) std::cout << i << ' '; std::cout << '\n'; */ break;
                case 6:
                    bdv(cmds[idx + 1]);
                    break;
                case 7:
                    cdv(cmds[idx + 1]);
                    break;
                default:
                    std::cout << "invalid command " << cmds[idx] << std::endl;
                    break;
            }
            idx = next;
        }
        return output;
    };

    auto output = solve(cmds, data[0], data[1], data[2]);
    std::ostringstream os;
    bool first = true; for (auto i : output) { os << (first?"":",") << i; first = false; }
    ans1 = os.str();

    ans2 = std::numeric_limits<uint64_t>::max();

    const std::vector<int> m(cmds.begin(),cmds.begin()+2);
    std::deque<uint64_t> q;
    q.emplace_back(0);
    for(size_t l = 1; l <= cmds.size(); l++) {
        std::vector<int> tmp(cmds.begin()+cmds.size()-l, cmds.end());
        decltype(q) next;
        while(!q.empty()) {
            auto a = q.front(); q.pop_front();
            a <<= 3;
            for (uint64_t i = 0; i < 8; i++) {
                auto res = solve(cmds, a | i, 0, 0);
                if (res == tmp) {
                    next.push_back(a|i);
                    if(l == cmds.size() and (a|i) < ans2) ans2 = a|i;
                }
            }
        }
        q.swap(next);
    }


    return {std::move(ans1), std::to_string(ans2)};
}
