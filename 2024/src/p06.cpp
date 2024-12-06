#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>

std::tuple<std::string, std::string> p06(const std::string &input) {
    int64_t ans1 = 0;
    int64_t ans2 = 0;

    std::vector<std::string> map;
    int x = 0, y = 0;
    int dx = 0, dy = -1;

    {
        bool first = true;
        for (const auto c: input) {
            if (c == '\n') first = true;
            else {
                if (c == '#' || c == '.' || c == '^') {
                    if (first) map.emplace_back();
                    first = false;
                    map.back().push_back(c);
                    if (c == '^') {
                        y = map.size() - 1;
                        x = map.back().size() - 1;
                    }

                }
            }
        }

    }

    const auto orig = map;
    auto oy = y, ox = x, ody = dy, odx = dx;

    while (x >= 0 && y >= 0 && y < map.size() && x < map[0].size()) {
        map[y][x] = 'X';
        auto get = [&map](int cy, int cx) {
            if (cy >= 0 && cy < map.size() && cx >= 0 && cx < map[0].size()) { return map[cy][cx]; }
            return '.';
        };
        if (get(y+dy,x+dx) == '#') {
            // -1 0 -> 0 1
            // 0 1 -> 1 0
            // 1 0 -> 0 -1
            // 0 -1 ->
            auto odx = dx;
            dx = -dy;
            dy = odx;
        } else {
            y += dy;
            x += dx;
        }
    }

    for (auto & s : map) {
        for (auto & c : s) {
            if (c=='X') ans1++;
        }
    }

    for (size_t r = 0; r < orig.size(); ++r) {
        for (size_t c = 0; c < orig[0].size(); ++c) {
            if (orig[r][c] == '#' || orig[r][c] == '^') continue;
            map = orig;
            y = oy; x = ox; dy = ody; dx = odx;
            map[r][c] = '#';
            auto dir = 1;
            std::vector<std::vector<int>> visits(orig.size(), std::vector<int>(orig[0].size(), 0));

            while (x >= 0 && y >= 0 && y < map.size() && x < map[0].size()) {
                if (visits[y][x] & dir) {
                    ans2++;
                    break;
                }
                visits[y][x] |= dir;
                map[y][x] = 'X';
                auto get = [&map](size_t cy, size_t cx) {
                    if (cy >= 0 && cy < map.size() && cx >= 0 && cx < map[0].size()) { return map[cy][cx]; }
                    return '.';
                };
                if (get(y+dy,x+dx) == '#') {
                    auto odx = dx;
                    dx = -dy;
                    dy = odx;
                    dir <<= 1;
                    if (dir > 8) dir = 1;
                } else {
                    y += dy;
                    x += dx;
                }
            }
        }
    }

    return {std::to_string(ans1), std::to_string(ans2)};
}
