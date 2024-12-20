#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <map>
#include <set>
#include <queue>
#include <limits>

std::tuple<std::string, std::string> p20(const std::string &input) {
    int64_t ans1 = 0;
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
    auto get = [&map](int r, int c) {
        if (r < 0 || c < 0 || r >= map.size() || c >= map[0].size()) return 'x';
        return map[r][c];
    };
    std::vector costs(map.size(), std::vector(map[0].size(), -1));
    std::vector<std::tuple<int,int>> path;
    {
        std::queue<std::tuple<int,int,int>> q; // posr,posc,steps,visited
        q.emplace(startr,startc,0);
        while (!q.empty()) {
            auto [r,c,s] = q.front(); q.pop();
            if (costs[r][c] != -1) continue;
            if (get(r,c) != '.') continue;
            costs[r][c] = s;
            path.emplace_back(r,c);

            q.emplace(r+1,c,s+1);
            q.emplace(r-1,c,s+1);
            q.emplace(r,c+1,s+1);
            q.emplace(r,c-1,s+1);
        }
    }

    for(auto p : {1,2}) {
        const int N = p==1?2:20;
        for (auto [r, c]:path) {
            for (int dr = -N; dr <= N; dr++) {
                for (int dc = -N; dc <= N; dc++) {
                    auto len = abs(dr) + abs(dc);
                    if (len > N) continue;
                    if (get(r + dr, c + dc) == 'x') continue;
                    if (costs[r + dr][c + dc] < 0) continue;
                    if (costs[r + dr][c + dc] - costs[r][c] > len) {
                        if (costs[r + dr][c + dc] - costs[r][c] - len >= 100) (p==1?ans1:ans2)++;
                    }
                }
            }
        }
    }

    return {std::to_string(ans1), std::to_string(ans2)};
}
