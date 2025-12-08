#include "aoc.h"
#include <vector>
#include <algorithm>
#include <tuple>

std::tuple<std::string, std::string> p08(const std::string &input) {
    uint64_t ans1 = 0;
    uint64_t ans2 = 0;
    std::vector<std::tuple<int64_t,int64_t,int64_t>> nums;
    {
        int num = 0;
        bool havenum = false;
        std::vector<int> tmp;
        for (const auto c: input) {
            if (c >= '0' && c <= '9') {
                num *= 10;
                num += c - '0';
                havenum = true;
            } else {
                if (havenum) {
                    tmp.push_back(num);
                }
                havenum = false;
                num = 0;
                if (c == '\n') {
                    if (tmp.size() == 3) {
                        nums.emplace_back(tmp[0], tmp[1], tmp[2]);
                    }
                    tmp.clear();
                }
            }
        }

    }

    std::vector<size_t> setidx(nums.size());
    for (size_t idx = 0; idx < nums.size(); ++idx) {
        setidx[idx] = idx;
    }

    std::vector<std::tuple<int64_t,size_t,size_t>> dists;
    dists.reserve(nums.size()*nums.size());

    for (size_t i = 0; i < nums.size(); ++i) {
        auto [x1,y1,z1] = nums[i];
        for (size_t j = i+1; j < nums.size(); ++j) {
            auto [x2,y2,z2] = nums[j];
            dists.emplace_back((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2),i,j);
        }
    }

    size_t tosort = std::min(dists.size(), size_t(6000));
    std::vector setsize(nums.size(), size_t(1));
    std::partial_sort(dists.begin(), dists.begin()+tosort, dists.end());
    size_t idx = 0;
    for (auto [d,a,b] : dists) {
        auto sa = setidx[a];
        auto sb = setidx[b];
        if (sa!=sb) {
            setsize[sa] += setsize[sb];
            setsize[sb] = 0;
            for (auto & s : setidx) {
                if (s == sb) s = sa;
            }
        }
        if (setsize[sa] == setsize.size()) {
            ans2 = std::get<0>(nums[a])*std::get<0>(nums[b]);
            break;
        }
        idx++;
        if (idx == 1000) {
            auto cpy = setsize;
            std::sort(cpy.begin(), cpy.end(),std::greater<>());
            ans1 = cpy[0]*cpy[1]*cpy[2];
        }
        if (idx == tosort) {
            tosort = std::min(tosort+3000, dists.size());
            partial_sort(dists.begin()+idx, dists.begin()+tosort, dists.end());
        }
    }

    return {std::to_string(ans1), std::to_string(ans2)};
}
