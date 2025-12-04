#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>

std::tuple<std::string, std::string> p04(const std::string &input) {
    int64_t ans1 = 0;
    int64_t ans2 = 0;
    std::vector<std::string> v;
    {
        bool first = true;
        for (const auto c: input) {
            if (c == '.' || c == '@') {
                if (first) {
                    v.emplace_back();
                    first = false;
                }
                v.back().push_back(c);
            } else if (c == '\n'){
                first = true;
            }
        }

    }
    bool done = false;
    int iter = 0;
    while (!done) {
        for (size_t r = 0; r < v.size(); ++r) {
            for (size_t c = 0; c < v[r].size(); ++c) {
                if (v[r][c] == '.') continue;
                int n = 0;
                for (int dr = (r==0?0:-1); dr <= (r==v.size()-1?0:1); ++dr) {
                    for (int dc = (c == 0?0:-1); dc <= (c==v[r].size()-1?0:1); ++dc) {
                        if (dr == 0 && dc == 0) continue;
                        if (v[r+dr][c+dc] != '.') n++;
                    }
                }
                if (n < 4) {
                    v[r][c] = 'x';
                    if (iter == 0) ans1++;
                }
            }
        }

        done = true;
        for (auto & s : v) for (auto & c : s) {
            if (c == 'x') {
                c = '.';
                ans2++;
                done = false;
            }
        }
        iter++;
    }
    return {std::to_string(ans1), std::to_string(ans2)};
}
