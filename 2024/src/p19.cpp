#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>
#include <map>

static uint64_t solve(std::map<std::string, uint64_t> &m, const std::vector<std::string> & ts, const std::string & d) {
    auto it = m.find(d);
    if (it != m.end()) { return it->second; }
    if (d.empty()) { return 1; }
    uint64_t ret = 0;
    for ( const auto & t : ts ) {
        bool ok = true;
        for (size_t j = 0; j < t.size(); j++) {
            if (j>= d.size() || d[j] != t[j]) { ok = false; break; }
        }
        if (ok) {
            ret += solve(m, ts, d.substr(t.size()));
        }
    }
    m[d] = ret;
    return ret;
}

std::tuple<std::string, std::string> p19(const std::string &input) {
    uint64_t ans1 = 0;
    uint64_t ans2 = 0;

    std::vector<std::string> towels;
    std::vector<std::string> designs;

    {
        std::string tmp;
        bool first = true;
        for (const auto c: input) {
            if (c >= 'a' && c <= 'z') {
                tmp.push_back(c);
            } else {
                if (!tmp.empty()) {
                    if (first) {
                        towels.push_back(tmp);
                    } else {
                        designs.push_back(tmp);
                    }
                    if (c == '\n') first = false;
                }
                tmp.clear();
            }
        }

    }
    std::map<std::string, uint64_t> map;
    for (const auto & d : designs) {
        auto x = solve(map, towels, d);
        if (x) ans1++;
        ans2 += x;
    }
    return {std::to_string(ans1), std::to_string(ans2)};
}
