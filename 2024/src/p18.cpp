#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>
#include <queue>
std::tuple<std::string, std::string> p18(const std::string &input) {
    int64_t ans1 = 0;
    std::string ans2;

    const size_t SIZE = 70;
    const size_t STEPS = 1024;
    std::vector<std::tuple<int,int>> data;
    {
        int num = 0;
        bool havenum = false;
        std::vector<int> tmp;
        for (const auto c: input) {
            if (c >= '0' && c <= '9') {
                num *= 10;
                num += c - '0';
                havenum = true;
            } else {
                if (havenum) {
                    tmp.push_back(num);
                    if (tmp.size() == 2) {
                        data.emplace_back(tmp[0], tmp[1]);
                        tmp.clear();
                    }
                }
                havenum = false;
                num = 0;
            }
        }

    }
    std::vector map(SIZE+1, std::string(SIZE+1, '.'));
    {
        for (size_t step = 0; step < STEPS; ++step) {
            auto [x,y] = data[step];
            map[y][x] = '#';
        }
        std::vector cost(SIZE+1, std::vector(SIZE+1, std::numeric_limits<int>::max()));

        std::deque<std::tuple<int,int,int>> q;
        q.emplace_back(0,0,0);
        auto get = [&map](int x, int y) {
            if (y < 0 || x < 0 || y >= map.size() || x >= map[0].size()) return '#';
            else return map[y][x];
        };
        while (!q.empty()) {
            auto [x,y,c] = q.front(); q.pop_front();
            if (get(x,y) == '#') continue;
            if (cost[y][x] <= c) continue;
            cost[y][x] = c;
            q.emplace_back(x+1,y,c+1);
            q.emplace_back(x-1,y,c+1);
            q.emplace_back(x,y+1,c+1);
            q.emplace_back(x,y-1,c+1);
        }
        ans1 = cost[SIZE][SIZE];
    }

    for (int steps = STEPS; steps < data.size(); steps++) {
        int i = 0;
        {
            auto [x,y] = data[steps];
            map[y][x] = '#';
        }
        std::vector cost(SIZE+1, std::vector(SIZE+1, std::numeric_limits<int>::max()));

        std::deque<std::tuple<int,int,int>> q;
        q.emplace_back(0,0,0);
        auto get = [&map](int x, int y) {
            if (y < 0 || x < 0 || y >= map.size() || x >= map[0].size()) return '#';
            else return map[y][x];
        };
        while (!q.empty()) {
            auto [x,y,c] = q.front(); q.pop_front();
            if (get(x,y) == '#') continue;
            if (cost[y][x] <= c) continue;
            cost[y][x] = c;
            q.emplace_back(x+1,y,c+1);
            q.emplace_back(x-1,y,c+1);
            q.emplace_back(x,y+1,c+1);
            q.emplace_back(x,y-1,c+1);
        }
        if (cost[SIZE][SIZE] == std::numeric_limits<int>::max()) {
            auto [x,y] = data[steps];
            ans2 = std::to_string(x) + ',' + std::to_string(y);
            break;
        }
    }

    return {std::to_string(ans1), ans2};
}
