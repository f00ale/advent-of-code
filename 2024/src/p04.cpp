#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>

std::tuple<std::string, std::string> p04(const std::string &input) {
    int64_t ans1 = 0;
    int64_t ans2 = 0;
    std::vector<std::string> v;
    {
        int num = 0;
        bool havenum = false;
        bool first = true;
        for (const auto c: input) {
          if(c >= 'A' && c <= 'Z') {
            if(first) {
               v.emplace_back();
               first = false;
            }
            v.back().push_back(c);
          } else if(c == '\n') {
            first = true;
          }

        }

    }

    auto get = [&v](size_t r, size_t c) {
      if(r >= 0 && c >= 0 && r < v.size() && c < v[0].size()) {
        return v[r][c];
      }
      return ' ';
    };
    for(size_t r = 0; r < v.size(); r++) {
      for(size_t c = 0; c < v[r].size(); c++) {
        if(get(r, c) == 'X') {
          if(get(r, c + 1) == 'M' && get(r, c + 2) == 'A' && get(r, c + 3) == 'S') ans1++;
          if(get(r, c - 1) == 'M' && get(r, c - 2) == 'A' && get(r, c - 3) == 'S') ans1++;
          if(get(r + 1, c) == 'M' && get(r + 2, c) == 'A' && get(r + 3, c) == 'S') ans1++;
          if(get(r - 1, c) == 'M' && get(r - 2, c) == 'A' && get(r - 3, c) == 'S') ans1++;

          if(get(r + 1, c + 1) == 'M' && get(r + 2, c + 2) == 'A' && get(r + 3, c + 3) == 'S') ans1++;
          if(get(r + 1, c - 1) == 'M' && get(r + 2, c - 2) == 'A' && get(r + 3, c - 3) == 'S') ans1++;
          if(get(r - 1, c + 1) == 'M' && get(r - 2, c + 2) == 'A' && get(r - 3, c + 3) == 'S') ans1++;
          if(get(r - 1, c - 1) == 'M' && get(r - 2, c - 2) == 'A' && get(r - 3, c - 3) == 'S') ans1++;
        }
      }
    }

  for(size_t r = 0; r < v.size(); r++) {
    for(size_t c = 0; c < v[r].size(); c++) {
      if(get(r, c) == 'A') {
        bool d1 = false, d2 = false;
        if(get(r-1, c-1) == 'M' && get(r+1, c+1) == 'S') d1 = true;
        if(get(r-1, c-1) == 'S' && get(r+1, c+1) == 'M') d1 = true;

        if(get(r-1, c+1) == 'M' && get(r+1, c-1) == 'S') d2 = true;
        if(get(r-1, c+1) == 'S' && get(r+1, c-1) == 'M') d2 = true;

        if(d1&&d2) ans2++;

      }
    }
  }


    return {std::to_string(ans1), std::to_string(ans2)};
}
