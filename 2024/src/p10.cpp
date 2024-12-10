#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>

int rec(const std::vector<std::vector<int>> & map, ssize_t r, ssize_t c, std::set<std::tuple<ssize_t, ssize_t>> & set, int num = 0) {
    if (r < 0 || c < 0 || r >= map.size() || c >= map[0].size()) return 0;
    if (map[r][c] != num) return 0;
    if (map[r][c] == 9) { set.emplace(r,c); return 1; }
    return rec(map, r-1, c, set, num+1)+rec(map,r+1,c,set,num+1)+rec(map,r,c-1,set,num+1)+rec(map,r,c+1,set,num+1);
}

std::tuple<std::string, std::string> p10(const std::string &input) {
    int64_t ans1 = 0;
    int64_t ans2 = 0;
    std::vector<std::vector<int>> map;
    {

        bool first = true;
        for (const auto c: input) {
            if (c >= '0' && c <= '9') {
                if (first) {map.emplace_back(); }
                first = false;
                map.back().push_back(c - '0');
            } else if (c == '\n') first = true;
        }

    }


    for (ssize_t r = 0; r < map.size(); r++) {
        for (ssize_t c = 0; c < map[0].size(); c++) {
            std::set<std::tuple<ssize_t, ssize_t>> t;
            ans2+=rec(map, r, c, t);
            ans1 += t.size();
        }
    }

    return {std::to_string(ans1), std::to_string(ans2)};
}
