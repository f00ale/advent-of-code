#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>

static std::tuple<int,int,int> rec(std::vector<std::string> & map, char cur, ssize_t r, ssize_t c) {
    auto get = [](const std::vector<std::string> & map, ssize_t r, ssize_t c) {
        if (r < 0 || r >= map.size() || c < 0 || c >= map[0].size()) return '.';
        return map[r][c];
    };
    if (islower(cur)) return {0,0,0};
    if(get(map,r,c) == '.') return {0,0,0};
    if (map[r][c] == tolower(cur)) return {0,0,0};
    if (map[r][c] != cur && map[r][c] != tolower(cur)) return {0,0,0};
    int corners = 0, perim = 0;
    for(int dr = -1; dr <= 1; dr++) {
        for(int dc = -1; dc <= 1; dc++) {
            if (dr && dc) {
                if((toupper(get(map,r,c)) != toupper(get(map,r+dr,c))) && (toupper(get(map,r,c)) != toupper(get(map,r,c+dc)))) corners++; // ytterhörn
                if(cur == toupper(get(map,r+dr,c)) && cur == toupper(get(map,r,c+dc)) && cur != toupper(get(map, r+dr, c+dc))) corners++; // innerhörn
            } else if (dr || dc) {
                if (cur != toupper(get(map, r+dr, c+dc))) perim++;
            }
        }
    }
    map[r][c] = tolower(map[r][c]);
    auto [ua,up,uc] = rec(map, cur, r-1, c);
    auto [da,dp,dc] = rec(map, cur, r+1, c);
    auto [la,lp,lc] = rec(map, cur, r, c-1);
    auto [ra,rp,rc] = rec(map, cur, r, c+1);
    return {1+ua+da+la+ra, perim+up+dp+lp+rp, corners+uc+dc+lc+rc};
}

std::tuple<std::string, std::string> p12(const std::string &input) {
    int64_t ans1 = 0;
    int64_t ans2 = 0;
    std::vector<std::string> map;
    {
        bool first = true;
        for (const auto c: input) {
            if (c >= 'A' && c <= 'Z') {
                if (first) {map.emplace_back();}
                map.back().push_back(c);
                first = false;
            } else {
                if (c=='\n') first = true;
            }
        }

    }

    auto m2 = map;
    for (ssize_t r = 0; r < map.size(); r++) {
        for (ssize_t c = 0; c < map[r].size(); c++) {
            auto [area, perim, sides] = rec(m2, m2[r][c], r, c);
            ans1 += area * perim;
            ans2 += area * sides;
        }
    }

    return {std::to_string(ans1), std::to_string(ans2)};
}
