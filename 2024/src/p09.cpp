#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>

std::tuple<std::string, std::string> p09(const std::string &input) {
    int64_t ans1 = 0;
    int64_t ans2 = 0;
    std::vector<int16_t> disk;
    std::vector<std::tuple<int16_t, int>> blocks; // id, len
    {
        bool even = true;
        int16_t id = 0;
        for (const auto c: input) {
            if (c >= '0' && c <= '9') {
                int16_t tmp = even ? id : -1;
                if (even) id++;
                even = !even;
                int num = c - '0';
                blocks.emplace_back(tmp, num);
                for (int i = 0; i < num; i++) {
                    disk.push_back(tmp);
                }
            }
        }

    }

    {
        ssize_t front = 0;
        ssize_t back = disk.size() - 1;
        while (true) {
            while (disk[front] >= 0) front++;
            while (disk[back] < 0) back--;
            if (back < front) break;
            std::swap(disk[front], disk[back]);
        }
    }
    for (size_t i = 0; i < disk.size(); i++) {
        if (disk[i] < 0) break;
        ans1 += i * disk[i];
    }

    {
        int16_t nextid = 0;
        for (auto [id,len] : blocks) {
            if (id > nextid) nextid = id;
        }

        while (nextid > 0) {
            auto nextpos = std::find_if(blocks.begin(), blocks.end(), [nextid](const std::tuple<int16_t, int> &x) { return std::get<0>(x) == nextid; });
            if (nextpos == blocks.end()) { nextid--; continue; }
            auto [nid,nlen] = *nextpos;
            for (auto it = blocks.begin(); it != nextpos; it++) {
                auto [id, len] = *it;
                if (id >= 0) continue;
                if (len == nlen) {
                    std::swap(std::get<0>(*nextpos), std::get<0>(*it));
                    break;
                } else if (len > nlen) {
                    std::swap(std::get<0>(*nextpos), std::get<0>(*it));
                    std::get<1>(*it) = nlen;
                    blocks.insert(it+1, std::make_tuple(-1, len-nlen));
                    break;
                }

            }
            nextid--;
        }

    }

    int pos = 0;
    for (auto it = blocks.begin(); it != blocks.end(); it++) {
        auto [id, len] = *it;
        if (id > 0) {
            for (int i = 0; i< len; i++) {
                ans2 += static_cast<int64_t>(id) * (pos+i);
            }
        }
        pos += len;
    }

    return {std::to_string(ans1), std::to_string(ans2)};
}
