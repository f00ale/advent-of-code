#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>

std::tuple<std::string, std::string> p25(const std::string &input) {
    int64_t ans1 = 0;

    std::vector<std::vector<int>> keys;
    std::vector<std::vector<int>> locks;
    {
        std::vector<std::string> current;
        bool first = true;
        for (const auto c: input) {
            if (c == '#' || c == '.') {
                if (first) current.emplace_back();
                first = false;
                current.back().push_back(c);
            } else if (c == '\n') {
                first = true;
                if (current.size() == 7) {
                    if (current[0][0] == '#') {
                        //lock
                        locks.emplace_back();
                        for (size_t i = 0; i < current[0].size(); ++i) {
                            for (size_t j = 0; j < current.size(); ++j) {
                                if (current[j][i] == '.') {
                                    locks.back().push_back(j-1);
                                    break;
                                }
                            }
                        }
                    } else {
                        //key
                        keys.emplace_back();
                        for (size_t i = 0; i < current[0].size(); ++i) {
                            for (size_t j = current.size(); j > 0; --j) {
                                if (current[j-1][i] == '.') {
                                    keys.back().push_back(current.size()-j-1);
                                    break;
                                }
                            }
                        }

                    }

                    current.clear();
                }
            }
        }

    }

    for (auto & lock : locks) {
        for (auto & key : keys) {
            bool ok = true;
            for (size_t i = 0; i < key.size(); ++i) {
                if (key[i]+lock[i] >= 6) ok = false;
            }
            if (ok) ans1++;
        }
    }

    return {std::to_string(ans1), "-"};
}
