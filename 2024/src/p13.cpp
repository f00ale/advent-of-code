#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>

std::tuple<std::string, std::string> p13(const std::string &input) {
    int64_t ans1 = 0;
    int64_t ans2 = 0;
    std::vector<std::tuple<int64_t,int64_t,int64_t,int64_t,int64_t,int64_t>> nums;
    {
        int64_t num = 0;
        bool havenum = false;
        std::vector<int64_t> tmp;
        for (const auto c: input) {
            if (c >= '0' && c <= '9') {
                num *= 10;
                num += c - '0';
                havenum = true;
            } else {
                if(havenum) {
                    tmp.push_back(num);
                    if(tmp.size() == 6) {
                        nums.emplace_back(tmp[0], tmp[1], tmp[2], tmp[3], tmp[4], tmp[5]);
                        tmp.clear();
                    }
                }
                havenum = false;
                num = 0;
            }
        }

    }
    for (auto p : {1,2}) {
        for(auto [ax,ay,bx,by,x,y]:nums) {
            if(p == 2) {
                x += 10000000000000;
                y += 10000000000000;
            }
            // solve Ax=b -> x = A^-1b
            auto det = ax*by - bx*ay;
            auto act = by*x - bx*y;
            auto bct = -ay*x + ax*y;
            if((act % det == 0) && (bct % det == 0)) {
                auto ac = act / det;
                auto bc = bct / det;
                (p == 1 ? ans1 : ans2) += 3*ac + bc;
            }
        }
    }
    return {std::to_string(ans1), std::to_string(ans2)};
}
