#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <map>
#include <set>
#include <queue>
#include <limits>

std::tuple<std::string, std::string> p16(const std::string &input) {
    int ans1 = 0;
    int64_t ans2 = 0;
    std::vector<std::string> map;
    int startr = 0, endr = 0, startc = 0, endc = 0;
    {
        bool first = true;
        for (const auto c: input) {
            if (c == '#' || c == '.' || c == 'S' || c == 'E') {
                if (first) { map.emplace_back(); }
                first = false;
                if (c == 'S') {
                    startr = map.size() - 1;
                    startc = map.back().size();
                    map.back().push_back('.');
                }
                else if (c == 'E') {
                    endr = map.size() - 1;
                    endc = map.back().size();
                    map.back().push_back('.');
                }
                else map.back().push_back(c);
            } if (c =='\n') first = true;
        }

    }

    std::vector costs(4, std::vector(map.size(), std::vector(map[0].size(), std::numeric_limits<int>::max())));

    auto get = [&map](int r, int c) {
        if (r< 0 || c < 0 || r >= map.size() || c >= map.size()) return '#';
        else return map[r][c];
    };
    {
        std::queue<std::tuple<int,int,int,int>> q; // row col dir cost
        q.emplace(startr, startc, 0, 0);
        while (!q.empty()) {
            auto [r,c,d,cost] = q.front(); q.pop();
            if (get(r,c) == '#') continue;
            if (cost >= costs[d][r][c]) continue;
            costs[d][r][c] = cost;

            int dr = 0, dc = 0;
            switch (d) {
                case 0: dc = 1; break;
                case 1: dr = -1; break;
                case 2: dc = -1; break;
                case 3: dr = 1; break;
            }

            q.emplace(r+dr, c+dc, d, cost+1);

            q.emplace(r, c, (d+1)%4, cost+1000);
            q.emplace(r, c, (d+3)%4, cost+1000);
        }
    }

    ans1 = std::numeric_limits<int>::max();
    for (int i = 0; i < 4; i++) {
        ans1 = std::min(ans1, costs[i][endr][endc]);
    }

    std::queue<std::tuple<int,int,int,int>> q;
    for (int i = 0; i < 4; i++) {
        if (costs[i][endr][endc] == ans1) {
            q.emplace(endr, endc, i, ans1);
        }
    }

    while (!q.empty()) {
        auto [r,c,d,cost] = q.front(); q.pop();
        if (get(r,c) == '#') continue;
        if (costs[d][r][c] != cost) continue;
        map[r][c] = 'O';
        int dr = 0, dc = 0;
        switch (d) { // going backwards, flipped from above
            case 0: dc = -1; break;
            case 1: dr = 1; break;
            case 2: dc = 1; break;
            case 3: dr = -1; break;
        }
        q.emplace(r+dr, c+dc, d, cost-1);
        q.emplace(r, c, (d+1)%4, cost-1000);
        q.emplace(r, c, (d+3)%4, cost-1000);
    }
    for (auto & s : map) {
        for (auto & c : s) {
            if (c=='O') ans2++;
        }
    }

    return {std::to_string(ans1), std::to_string(ans2)};
}
