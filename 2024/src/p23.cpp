#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>
#include <map>
#include <queue>
#include <sstream>
#include <unordered_set>

std::tuple<std::string, std::string> p23(const std::string &input) {
    int64_t ans1 = 0;
    std::string ans2;
    std::vector<std::string> tokens;
    std::map<std::string, int> str2tok;
    std::vector<std::tuple<int, int>> data;
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
                    if (str2tok.find(tmp1) == str2tok.end()) {
                        str2tok[tmp1] = tokens.size();
                        tokens.push_back(tmp1);
                    }
                    if (str2tok.find(tmp2) == str2tok.end()) {
                        str2tok[tmp2] = tokens.size();
                        tokens.push_back(tmp2);
                    }
                    data.emplace_back(str2tok[tmp1], str2tok[tmp2]);
                }
                first = true;
                tmp1.clear();
                tmp2.clear();
            }
        }

    }

    {
        std::map<int, std::set<int>> map;
        for (auto [a,b]: data) {
            map[a].insert(a);
            map[b].insert(b);
            map[a].insert(b);
            map[b].insert(a);
        }
        std::set<std::set<int>> set;
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
                if (tokens[m][0] == 't') {
                    ans1++;
                    break;
                }
            }
        }

        auto tostr = [&tokens](const std::set<int> & s) {
            bool first = true;
            std::vector<std::string> tmp;
            tmp.reserve(s.size());
            for (auto i : s) {
                tmp.push_back(tokens[i]);
            }
            std::sort(tmp.begin(), tmp.end());
            std::ostringstream os;
            for (auto & n : tmp) {
                os << (first ? "" : ",") << n;
                first = false;
            }
            return os.str();
        };

        std::set<int> largest;
        std::set<std::set<int>> seen;
        for (auto & s : set) {
            std::queue<std::set<int>> q;
            q.emplace(s);
            while (!q.empty()) {
                const auto curr = q.front(); q.pop();
                if (seen.find(curr) != seen.end()) continue;
                seen.insert(curr);
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
