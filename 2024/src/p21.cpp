#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>
#include <map>

static std::vector<std::string> rec(const std::string & goal,
    const std::map<std::tuple<char,char>, std::vector<std::string>> & pressv,
    int level = 0,
    char curr = 'A',
    std::string::size_type cpos = 0) {
    //std::cout << goal << std::endl;
    std::vector<std::string> result;
    if (cpos == goal.size()) return {""};
    auto c = goal[cpos];
    auto tmp = rec(goal, pressv, level, c, cpos + 1);
    auto vit = pressv.find({curr,c});
    if (vit == pressv.end()) {
        std::cout << "ERROR " << curr << " -> " << c << '\n'; return {};
    }
    for (auto it = vit->second.begin(); it != vit->second.end(); ++it) {
        for (auto & x : tmp) result.push_back(*it + x);
    }
    return result;
}

static size_t recout(const std::string & goal,
    const std::map<std::tuple<char,char>, std::vector<std::string>> & pressv,
    int limit, int level = 0)
{
    if (level == limit) return goal.size();
    static std::map<std::tuple<size_t,std::string>, size_t> memo;
    auto it = memo.find({level,goal});
    if (it != memo.end()) {
        std::cout << "memo\n";
        return it->second;
    }
    size_t result = std::numeric_limits<size_t>::max();

    auto v = rec(goal, pressv);
    for (auto & s : v) {
        auto tmp = recout(s, pressv, limit, level + 1);
        if (tmp < result) result = tmp;
    }
    memo[{level,goal}] = result;
    return result;
}

static size_t solve(const char start, const char end,
    const std::map<std::tuple<char,char>, std::vector<std::string>> & pressv1,
    const std::map<std::tuple<char,char>, std::vector<std::string>> & pressv2,
    std::map<std::tuple<int, char,char>, size_t> & memo,
    int limit, const int level = 0) {
    if (level == limit) return 1;
    if (const auto it = memo.find({level,start,end}); it != memo.end()) {
        return it->second;
    }
    size_t result = std::numeric_limits<size_t>::max();
    auto & pressv = (level == 0 ? pressv1 : pressv2);
    auto it = pressv.find({start,end});
    if (it == pressv.end()) { std::cout << "ERROR\n"; return -1; }
    if (it->second.empty()) { std::cout << "ERROR\n"; return -1; }
    for ( auto & presses : it->second) {
        char curr = 'A';
        size_t len = 0;
        for (auto c : presses) {
            len += solve(curr, c, pressv1, pressv2, memo, limit, level + 1);
            curr = c;
        }
        if (len < result) result = len;
    }
    memo[{level,start,end}] = result;
    return result;
}

std::tuple<std::string, std::string> p21(const std::string &input) {
    uint64_t ans1 = 0;
    uint64_t ans2 = 0;

    auto isok = [](const std::string & input, const std::vector<std::string> & keypad, std::tuple<int,int> pos) {
        auto [r,c] = pos;
        for (auto ch : input) {
            switch (ch) {
                case '^': r--; break;
                case '<': c--; break;
                case 'v': r++; break;
                case '>': c++; break;
                case 'A': break;
                default: return false;
            }
            if (c < 0 || c >= keypad[0].size() || r < 0 || r >= keypad.size()) return false;
            if (keypad[r][c] == '#') return false;
        }
        return true;
    };

    auto replay = [](const std::string & input, const std::vector<std::string> & keypad, std::tuple<int,int> pos) {
        auto [r,c] = pos;
        std::string ret;
        for (auto ch : input) {
            switch (ch) {
                case '^': r--; break;
                case '<': c--; break;
                case 'v': r++; break;
                case '>': c++; break;
                case 'A': ret.push_back(keypad[r][c]); break;
            }
            if (c < 0 || c >= keypad[0].size() || r < 0 || r >= keypad.size()) return std::string("OUT OF RANGE");
            if (keypad[r][c] == '#') return std::string("FORBIDDEN POSITION");
        }
        return ret;
    };


    std::vector<std::string> keypad1 = {"789","456", "123", "#0A"};
    std::vector<std::string> keypad2 = { "#^A", "<v>" };

    std::vector<std::string> targets;

    {
        bool first = true;
        for (const auto c: input) {
            if ((c >= '0' && c <= '9') || c == 'A') {
                if (first) {
                    targets.emplace_back();
                    first = false;
                }
                targets.back().push_back(c);
            } else if (c== '\n') {
                first = true;

            }
        }

    }

    std::map<char, std::tuple<int,int>> pos1, pos2;
    for (int r=0; r<keypad1.size(); r++) for (int c=0; c<keypad1[r].size(); c++) pos1[keypad1[r][c]] = std::make_tuple(r,c);
    for (int r=0; r<keypad2.size(); r++) for (int c=0; c<keypad2[r].size(); c++) pos2[keypad2[r][c]] = std::make_tuple(r,c);

    const std::string keys1 = "A0123456789";
    const std::string keys2 = "A^<v>";

    std::map<std::tuple<char,char>, std::vector<std::string>> pressv2;
    for (const auto from:keys2) {
        for (const auto to:keys2) {
            const auto [r1,c1] = pos2[from];
            const auto [r2,c2] = pos2[to];
            if (c1 == c2 || r1 == r2) {
                std::string ret;
                if (r2 > r1) ret.append(r2-r1, 'v');
                if (c2 > c1) ret.append(c2-c1, '>');
                if (c2 < c1) ret.append(c1-c2, '<');
                if (r2 < r1) ret.append(r1-r2, '^');

                ret.push_back('A');
                pressv2[{from,to}] = { ret };
            } else {
                std::string ret;
                if (r2 > r1) ret.append(r2-r1, 'v');
                if (r2 < r1) ret.append(r1-r2, '^');
                if (c2 > c1) ret.append(c2-c1, '>');
                if (c2 < c1) ret.append(c1-c2, '<');

                ret.push_back('A');
                if (isok(ret, keypad2, pos2[from])) pressv2[{from,to}].push_back(ret);
                ret.clear();
                if (c2 > c1) ret.append(c2-c1, '>');
                if (c2 < c1) ret.append(c1-c2, '<');
                if (r2 > r1) ret.append(r2-r1, 'v');
                if (r2 < r1) ret.append(r1-r2, '^');

                ret.push_back('A');
                if (isok(ret, keypad2, pos2[from])) pressv2[{from,to}].push_back(ret);

            }
        }
    }
    std::map<std::tuple<char,char>, std::vector<std::string>> pressv1;
    for (auto from:keys1) {
        for (auto to:keys1) {
            auto [r1,c1] = pos1[from];
            auto [r2,c2] = pos1[to];
            if (c1 == c2 || r1 == r2) {
                std::string ret;
                if (r2 < r1) ret.append(r1-r2, '^');
                if (c2 < c1) ret.append(c1-c2, '<');
                if (c2 > c1) ret.append(c2-c1, '>');
                if (r2 > r1) ret.append(r2-r1, 'v');

                ret.push_back('A');
                pressv1[{from,to}] = { ret };
            } else {
                std::string ret;
                if (r2 < r1) ret.append(r1-r2, '^');
                if (r2 > r1) ret.append(r2-r1, 'v');
                if (c2 < c1) ret.append(c1-c2, '<');
                if (c2 > c1) ret.append(c2-c1, '>');

                ret.push_back('A');
                if (isok(ret, keypad1, pos1[from])) pressv1[{from,to}].push_back(ret);
                ret.clear();
                if (c2 < c1) ret.append(c1-c2, '<');
                if (c2 > c1) ret.append(c2-c1, '>');
                if (r2 < r1) ret.append(r1-r2, '^');
                if (r2 > r1) ret.append(r2-r1, 'v');

                ret.push_back('A');
                if (isok(ret, keypad1, pos1[from])) pressv1[{from,to}].push_back(ret);
            }
            //std::cout << from << " -> " << to << pressv1[{from,to}].size() << std::endl;

        }
    }

    std::map<std::tuple<char,char>, std::string> press2;
    for (const auto from:keys2) {
        for (const auto to:keys2) {
            const auto [r1,c1] = pos2[from];
            const auto [r2,c2] = pos2[to];
            std::string ret;
            if (r2 > r1) ret.append(r2-r1, 'v');
            if (c2 > c1) ret.append(c2-c1, '>');
            if (c2 < c1) ret.append(c1-c2, '<');
            if (r2 < r1) ret.append(r1-r2, '^');

            ret.push_back('A');
            //std::cout << from << "->" << to << ": (" << r1 << ',' << c1 << ')' << " -> (" << r2 << ',' << c2 << ": " << ret << std::endl;
            press2[{from,to}] = ret;
        }
    }

    std::map<std::tuple<char,char>, std::string> press1;
    for (auto from:keys1) {
        for (auto to:keys1) {
            auto [r1,c1] = pos1[from];
            auto [r2,c2] = pos1[to];
            std::string ret;
            if (r2 < r1) ret.append(r1-r2, '^');
            if (c2 < c1) ret.append(c1-c2, '<');
            if (c2 > c1) ret.append(c2-c1, '>');
            if (r2 > r1) ret.append(r2-r1, 'v');

            ret.push_back('A');
            press1[{from,to}] = ret;
        }
    }
    for (auto p : {1,2}) {
        std::map<std::tuple<int, char,char>, size_t> memo;
        for (const auto & s : targets) {
            size_t len = 0;
            char curr = 'A';
            for (auto c : s) {
                len += solve(curr, c, pressv1, pressv2, memo, (p==1?2:25)+1);
                curr = c;
            }
            size_t num=0;
            for (auto & c: s) {
                if (c >= '0' && c <= '9') num = num*10 + (c-'0');
            }
            (p==1?ans1:ans2) += num*len;
        }
    }

    return {std::to_string(ans1), std::to_string(ans2)};
}
