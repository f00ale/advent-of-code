#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>

std::tuple<std::string, std::string> p02(const std::string &input) {
    int64_t ans1 = 0;
    int64_t ans2 = 0;
    std::vector<std::vector<int>> vs;
    {
        int num = 0;
        bool havenum = false;
        bool first = true;
        for (const auto c: input) {
            if (c >= '0' && c <= '9') {
                num *= 10;
                num += c - '0';
                havenum = true;
            } else {
                if(havenum) {
                    if(first) vs.emplace_back();
                    first = false;
                    vs.back().push_back(num);
                }
                if(c == '\n') first = true;
                havenum = false;
                num = 0;
            }
        }

    }
    auto check = [](const std::vector<int> &v) {
       auto sgn = [](int i) { return i > 0 ? 1 : -1; };
        int diff = sgn(v[1] - v[0]);
        for(size_t i = 1; i < v.size(); i++) {
            if(abs(v[i] - v[i-1]) > 3) { return false; }
            if(sgn(v[i] - v[i-1]) != diff) { return false; }
            if(v[i] == v[i-1]) return false;
        }
        return true;
        };

    for(const auto & v : vs) {
      if(check(v)) { ans1++; ans2++; }
      else {
          for(size_t i = 0; i < v.size(); i++) {
             auto vc = v;
             vc.erase(vc.begin() + i);
             if(check(vc)) { ans2++; break; }
          }
      }
    }

    return {std::to_string(ans1), std::to_string(ans2)};
}
