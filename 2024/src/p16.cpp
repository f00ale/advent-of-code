#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <map>
#include <set>
#include <queue>
#include <limits>
struct Node {
    int r, c, d, s;
    std::set<std::tuple<int, int>> v;
    Node(int _r, int _c, int _d, int _s, std::set<std::tuple<int,int>> _v) : r(_r), c(_c), d(_d), s(_s), v(std::move(_v)) {}
};
bool operator<(const Node& lhs, const Node& rhs) { return lhs.s > rhs.s; }

std::tuple<std::string, std::string> p16(const std::string &input) {
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

    std::priority_queue<Node> q; // row, col, dir, score
    std::map<std::tuple<int,int,int>, int> visited; // row,col,dir -> score
    auto get = [&map](int r, int c) {
        if (r< 0 || c < 0 || r >= map.size() || c >= map.size()) return '#';
        else return map[r][c];
    };
    ans1 = std::numeric_limits<int64_t>::max();
    std::set<std::tuple<int,int>> visited1;
    q.emplace(startr, startc, 0, 0, visited1);
    while (!q.empty()) {
        auto [r,c,d,s,n] = q.top(); q.pop();
        if (s > ans1) continue;
        auto it = visited.find(std::make_tuple(r,c,d));
        if (it != visited.end()) {
            if (s > it->second) continue;
        }
        visited.emplace(std::make_tuple(r,c,d), s);
        n.emplace(r,c);
        if (r == endr && c == endc) {
            if (s <= ans1) {
                ans1 = s;
                for (auto t : n) visited1.insert(t);
            }
        }
        int dr = 0, dc = 0;
        switch (d) {
            case 0: dc = 1; break;
            case 1: dr = -1; break;
            case 2: dc = -1; break;
            case 3: dr = 1; break;
        }
        if (get(r+dr,c+dc) == '.') q.emplace(r+dr,c+dc,d,s+1,n);
        q.emplace(r,c,(d+1)%4,s+1000,n);
        q.emplace(r,c,(d+3)%4,s+1000,n);
    }
    ans2 = visited1.size();
    return {std::to_string(ans1), std::to_string(ans2)};
}
