#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>

std::tuple<std::string, std::string> p05(const std::string &input) {
    int64_t ans1 = 0;
    int64_t ans2 = 0;

    std::vector<std::tuple<int,int>> rules;
    std::vector<std::vector<int>> updates;

    {
        int num = 0;
        bool havenum = false;
        bool pipe = false;
        bool comma = false;
        std::vector<int> tmp;
        for (const auto c: input) {
            if (c >= '0' && c <= '9') {
                num *= 10;
                num += c - '0';
                havenum = true;
            } else {
                if(c == '|') pipe = true;
                if(c == ',') comma = true;
                if(havenum) tmp.push_back(num);
                havenum = false;
                num = 0;
                if(c == '\n') {
                    if(!tmp.empty()) {
                        if (pipe) {
                            rules.emplace_back(tmp[0], tmp[1]);
                        }
                        if(comma) {
                           updates.push_back(tmp);
                        }
                        tmp.clear();
                    }
                    pipe = comma = false;
                }
            }
        }

    }

    for(auto & u : updates) {
        bool ok = true;
        for(auto it1 = u.begin(); it1 != u.end(); ++it1) {
            for(auto it2 = it1+1; it2 != u.end(); ++it2) {
                bool t = false;
                for(auto [f,e] : rules) {
                    if(*it1 == f && *it2 == e) {
                      t = true;
                      std::swap(*it1, *it2);
                    }
                }
                ok = ok && t;
            }
        }
        if(ok) ans1 += u[u.size()/2];
        if(!ok) ans2 += u[u.size()/2];
    }

    return {std::to_string(ans1), std::to_string(ans2)};
}
