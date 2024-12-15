#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <deque>

std::tuple<std::string, std::string> p15(const std::string &input) {
    int64_t ans1 = 0;
    int64_t ans2 = 0;

    std::vector<std::string> map, map2;
    std::string moves;
    int robr = 0, robc = 0;
    int robr2 = 0, robc2 = 0;


    {
        bool first = true;
        for (const auto c: input) {
            if(c == '#' || c == '.' || c == 'O' || c == '@') {
                if(first) {map.emplace_back();map2.emplace_back();}
                if(c == '@') {
                    robr = map.size()-1;
                    robc = map.back().size();
                    map.back().push_back('.');
                    robr2 = map2.size()-1;
                    robc2 = map2.back().size();
                    map2.back().push_back('.');
                    map2.back().push_back('.');
                } else if (c == 'O') {
                    map.back().push_back(c);
                    map2.back().push_back('[');
                    map2.back().push_back(']');
                } else {
                    map.back().push_back(c);
                    map2.back().push_back(c);
                    map2.back().push_back(c);
                }
                first = false;
            }
            else if(c == '\n') first = true;
            else if(c == '<' || c == '>' || c == '^' || c == 'v') {
                moves.push_back(c);
            }
        }

    }

    auto get = [&map](int r, int c) {
        if(r < 0 || c < 0 || r >= map.size() || c >= map[0].size()) return '#';
        else return map[r][c];
    };
    auto get2 = [&map2](int r, int c) {
        if(r < 0 || c < 0 || r >= map2.size() || c >= map2[0].size()) return '#';
        else return map2[r][c];
    };

    for(auto m : moves) {
        int dr = 0, dc = 0;
        if(m == '<') dc = -1;
        else if(m == '>') dc = 1;
        else if(m == '^') dr = -1;
        else if(m == 'v') dr = 1;

        if(get(robr+dr, robc+dc) == '.') { robr+=dr; robc+=dc; }
        else if(get(robr+dr, robc+dc) == 'O') {
            for(int i = 2; ; i++) {
                if(get(robr+i*dr, robc+i*dc) == '#') break;
                if(get(robr+i*dr, robc+i*dc) == 'O') continue;
                map[robr+dr][robc+dc] = '.';
                map[robr+i*dr][robc+i*dc] = 'O';
                robr+=dr; robc+=dc;
                break;
            }
        }

        if(get2(robr2+dr, robc2+dc) == '.') { robr2+=dr; robc2+=dc; }
        else if(dc && (get2(robr2+dr, robc2+dc) == '[' || get2(robr2+dr, robc2+dc) == ']')) {
            for (int i = 2; ; i++) {
                if(get2(robr2+i*dr, robc2+i*dc) == '#') break;
                if(get2(robr2+i*dr, robc2+i*dc) == '[' || get2(robr2+i*dr, robc2+i*dc) == ']') continue;
                for (int j = i; j > 0; j--) {
                    map2[robr2][robc2+j*dc] = map2[robr2][robc2+(j-1)*dc];
                }
                map2[robr2+dr][robc2+dc] = '.';
                robr2+=dr; robc2+=dc;
                break;
            }
        } else if (dr && (get2(robr2+dr, robc2+dc) == '[' || get2(robr2+dr, robc2+dc) == ']')) {
            std::deque<std::tuple<int,int,int>> q; // row, c1, c2
            std::vector<std::tuple<int,int>> tomove;
            if (get2(robr2+dr, robc2+dc) == '[') q.emplace_back(robr2+dr, robc2, robc2+1);
            if (get2(robr2+dr, robc2+dc) == ']') q.emplace_back(robr2+dr, robc2-1, robc2);
            bool ok = true;
            while (!q.empty()) {
                auto [r,c1,c2] = q.front(); q.pop_front();
                if (get2(r+dr, c1) == '#' || get2(r+dr, c2) == '#') { ok = false; break; }
                if (get2(r+dr, c1) == '[') {
                    q.emplace_back(r+dr, c1, c2);
                }
                if (get2(r+dr, c1) == ']') {
                    q.emplace_back(r+dr, c1-1, c1);
                }
                if (get2(r+dr, c2) == '[') {
                    q.emplace_back(r+dr, c2, c2+1);
                }
                tomove.emplace_back(r,c1);

            }
            if (ok) {
                for (auto [r,c] : tomove) { map2[r][c] = '.'; map2[r][c+1] = '.'; }
                for (auto [r,c] : tomove) { map2[r+dr][c] = '['; map2[r+dr][c+1] = ']'; }
                robr2+=dr; robc2+=dc;
            }
        }
    }

    for(size_t r = 0; r < map.size(); r++) {
        for(size_t c = 0; c < map[r].size(); c++) {
            if(map[r][c] == 'O') ans1 += 100*r+c;
        }
    }
    for(size_t r = 0; r < map2.size(); r++) {
        for(size_t c = 0; c < map2[r].size(); c++) {
            if(map2[r][c] == '[') ans2 += 100*r+c;
        }
    }

    return {std::to_string(ans1), std::to_string(ans2)};
}
