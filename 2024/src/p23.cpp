#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>
#include <map>
#include <queue>
#include <sstream>

std::tuple<std::string, std::string> p23(const std::string &input) {
    int64_t ans1 = 0;
    std::string ans2;
    std::vector<std::tuple<std::string, std::string>> data;
    {
        std::string tmp1, tmp2;
        bool first = true;
        for (const auto c: input) {
            if (c >= 'a' && c <= 'z') {
                if (first) tmp1.push_back(c);
                else tmp2.push_back(c);
            } else if (c=='-') {
                first = false;
            } else if (c=='\n') {
                if (tmp1.size() == 2 && tmp2.size() == 2) {
                    data.emplace_back(tmp1, tmp2);
                }
                first = true;
                tmp1.clear();
                tmp2.clear();
            }
        }

    }


    {
        std::map<std::string, std::set<std::string>> map;
        for (auto [a,b]: data) {
            map[a].insert(a);
            map[b].insert(b);
            map[a].insert(b);
            map[b].insert(a);
        }
        std::set<std::set<std::string>> set;
        for (auto & [a,b]: data) {
            auto & s1 = map[a];
            auto & s2 = map[b];
            for (auto & m : s1) {
                if (m == a || m == b) continue;
                if (auto it = s2.find(m); it != s2.end()) {
                    set.emplace(std::set{a,b,m});
                }
            }
        }

        for (auto & s : set) {
            for (auto & m : s) {
                if (m[0] == 't') {
                    ans1++;
                    break;
                }
            }
        }

        auto tostr = [](const std::set<std::string> & s) {
            bool first = true;
            std::ostringstream os;
            for (auto & n : s) {
                os << (first ? "" : ",") << n;
                first = false;
            }
            return os.str();
        };

        std::set<std::string> largest;
        std::set<std::string> seen;
        for (auto & s : set) {
            std::queue<std::set<std::string>> q;
            q.emplace(s);
            while (!q.empty()) {
                const auto curr = q.front(); q.pop();
                auto str = tostr(curr);
                if (seen.find(str) != seen.end()) continue;
                seen.insert(str);
                if (curr.size() > largest.size()) { largest = curr; }
                auto candidates = map[*curr.begin()];
                for (auto & c : curr) {
                    auto & cs = map[c];
                    decltype(candidates) next;
                    std::set_intersection(candidates.begin(), candidates.end(), cs.begin(), cs.end(), std::inserter(next, next.begin()));
                    candidates.swap(next);
                }

                decltype(candidates) next;
                std::set_difference(candidates.begin(), candidates.end(), curr.begin(), curr.end(), std::inserter(next, next.begin()));
                for (auto & n : next) {
                    auto cpy = curr;
                    cpy.insert(n);
                    q.emplace(std::move(cpy));
                }
            }
        }

        ans2 = tostr(largest);
    }

    return {std::to_string(ans1), ans2};
}
