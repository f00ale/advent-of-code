#include "aoc.h"
#include <vector>
#include <tuple>

std::tuple<std::string, std::string> p08(const std::string &input) {
    int64_t ans1 = 0;
    int64_t ans2 = 0;
    std::vector<std::string> map;
    {
        bool first = true;
        for (const auto c: input) {
            if (c == '\n') first = true;
            else {
                if (first) {map.emplace_back();}
                first = false;
                map.back().push_back(c);
            }
        }

    }

    std::vector<std::vector<std::tuple<int,int>>> positions(256);
    for (int r = 0; r < map.size(); ++r) {
        for (int c = 0; c < map[r].size(); ++c) {
            if (map[r][c] != '.') {
                positions[map[r][c]].emplace_back(r, c);
            }
        }
    }
    auto cpy = map;
    for (auto & v : positions) {
        if (!v.empty()) {
            for (auto it1 = v.begin(); it1 != v.end(); ++it1) {
                auto [r1,c1] = *it1;
                for (auto it2 = it1+1; it2 != v.end(); ++it2) {
                    auto [r2,c2] = *it2;
                    auto dr = r1 - r2;
                    auto dc = c1 - c2;

                    auto nr1 = r2 - dr;
                    auto nc1 = c2 - dc;
                    auto nr2 = r1 + dr;
                    auto nc2 = c1 + dc;
                    if (nr1 >= 0 && nr1 < map.size() && nc1 >= 0 && nc1 < map[0].size()) {
                        map[nr1][nc1] = '#';
                    }
                    if (nr2 >= 0 && nr2 < map.size() && nc2 >= 0 && nc2 < map[0].size()) {
                        map[nr2][nc2] = '#';
                    }
                }
            }
        }
    }

    for (auto & s : map) for (auto c : s) if (c=='#') ans1++;

    for (auto & v : positions) {
        if (!v.empty()) {
            for (auto it1 = v.begin(); it1 != v.end(); ++it1) {
                auto [r1,c1] = *it1;
                for (auto it2 = it1+1; it2 != v.end(); ++it2) {
                    auto [r2,c2] = *it2;
                    auto dr = r1 - r2;
                    auto dc = c1 - c2;

                    for (int t = 0; ; t++) {
                        auto nr = r1 + t*dr;
                        auto nc = c1 + t*dc;
                        if (nr >= 0 && nr < map.size() && nc >= 0 && nc < map[0].size()) {
                            map[nr][nc] = '#';
                        } else break;
                    }
                    for (int t = 0; ; t++) {
                        auto nr = r1 - t*dr;
                        auto nc = c1 - t*dc;
                        if (nr >= 0 && nr < map.size() && nc >= 0 && nc < map[0].size()) {
                            map[nr][nc] = '#';
                        } else break;
                    }
                }
            }
        }
    }

    for (auto & s : map) for (auto c : s) if (c=='#') ans2++;

    return {std::to_string(ans1), std::to_string(ans2)};
}
