#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>
#include <map>
#include <queue>
#include <sstream>

std::tuple<std::string, std::string> p24(const std::string &input) {
    uint64_t ans1 = 0;
    std::string ans2;

    std::map<std::string, uint64_t> regs;
    std::vector<std::tuple<std::string, std::string, std::string, std::string>> cmds;

    {
        std::vector <std::string> tmp;
        bool first = true;

        for (const auto c: input) {
            if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                if (first) { tmp.emplace_back(); }
                first = false;
                tmp.back().push_back(c);
            } else {
                first = true;
                if (c == '\n') {
                    if (tmp.size() == 2) {
                        regs[tmp[0]] = std::stoi(tmp[1]);
                    }
                    if (tmp.size() == 4) {
                        cmds.emplace_back(tmp[0], tmp[1], tmp[2], tmp[3]);
                    }
                    tmp.clear();
                }
            }
        }

    }

    decltype(cmds) ordered_cmds;
    {
        std::deque<std::tuple<std::string, std::string, std::string, std::string>> q(cmds.begin(), cmds.end());
        while (!q.empty()) {
            const auto [r1, cmd, r2, target] = q.front(); q.pop_front();
            if (regs.find(r1) == regs.end()) { q.emplace_back(r1, cmd, r2, target); continue; }
            if (regs.find(r2) == regs.end()) { q.emplace_back(r1, cmd, r2, target); continue; }
            ordered_cmds.emplace_back(r1, cmd, r2, target);
            if (cmd == "OR") {
                regs[target] = regs[r1] | regs[r2];
            } else if (cmd == "AND") {
                regs[target] = regs[r1] & regs[r2];
            } else if (cmd == "XOR") {
                regs[target] = regs[r1] ^ regs[r2];
            } else {
                std::cout << "unknown command: " << cmd << std::endl;
            }
        }
    }

    for (auto & [reg,val] : regs) {
        if (reg[0] == 'z') {
            auto shift = std::stoll(reg.substr(1));
            ans1 |= (val << shift);
        }

    }

    std::map<std::string, std::string> swaps;
    auto add_swap = [&swaps](const std::string &a, const std::string &b) {
        swaps[a] = b;
        swaps[b] = a;
    };

    // hardcoded, solved "by hand"
    add_swap("z06", "fkp");
    add_swap("z11", "ngr");
    add_swap("z31", "mfm");
    add_swap("bpt", "krj");

    for (auto & [r1, cmd, r2, target] : cmds) {
        //if (auto it = swaps.find(r1); it != swaps.end()) {
        //    r1 = it->second;
        //}
        //if (auto it = swaps.find(r2); it != swaps.end()) {
        //    r2 = it->second;
        //}
        if (auto it = swaps.find(target); it != swaps.end()) {
            target = it->second;
        }
    }



    auto istype = [](const std::string & name, char type) {
        if (name.length() != 3) return false;
        if (name[0] == type && (name[1] >= '0' && name[1] <= '9') && (name[2] >= '0' && name[2] <= '9')) return true;
        return false;
    };

    auto isreg = [](const std::string & name) {
        if (name.length() != 3) return false;
        if (name[0] != 'x' && name[0] != 'y' && name[0] != 'z') return false;
        if (!(name[1] >= '0' && name[1] <= '9') || !(name[2] >= '0' && name[2] <= '9')) return false;
        return true;
    };
    auto isdig = [istype](const std::string & name) {
        return istype(name, 'd');
    };
    auto regnum = [](const std::string & name) {
        if (name.length() != 3) return -1;
        if (!(name[1] >= '0' && name[1] <= '9') || !(name[2] >= '0' && name[2] <= '9')) return -1;
        return std::stoi(name.substr(1));
    };

    int changed = 1;
    int iter = 0;
    std::map<std::string, std::string> replacements;
    /*
    for (auto & [r1,op,r2,ta] : ordered_cmds) {
        if (auto it = replacements.find(r1); it != replacements.end()) { r1 = it->second; }
        if (auto it = replacements.find(r2); it != replacements.end()) { r2 = it->second; }
        if (!isreg(ta)) {
            replacements.emplace(ta, "("+r1+op+r2+")");
        }
    }
*/
    while (false && changed && iter++ < 15) {
        changed = 0;
        for (auto & [r1,op,r2,ta] : ordered_cmds) {
            if (op== "XOR") {
                if (isreg(r1) && isreg(r2) && !isreg(ta)) {
                    if (regnum(r1) == regnum(r2)) { replacements[ta] = "d"+r1.substr(1); }
                }
//                if (istype(r1, 'c') && istype(r2, 'd') && && !isreg(ta)) {}
            } else if (op== "AND") {
                if (isreg(r1) && isreg(r2) && !isreg(ta)) {
                    if (regnum(r1) == regnum(r2)) { replacements[ta] = (regnum(r1) == 0? "c":"a")+r1.substr(1); }
                } else if (istype(r1, 'c') && istype(r2, 'd') && regnum(r1)+1 == regnum(r2)) {
                    replacements[ta] = "b"+r1.substr(1);
                } else if (istype(r1, 'd') && istype(r2, 'c') && regnum(r1) == regnum(r2)+1) {
                    replacements[ta] = "b"+r2.substr(1);
                }
            } else if (op== "OR") {
                if (istype(r1, 'b') && istype(r2,'a') && !isreg(ta)) replacements[ta] = "c"+r2.substr(1);
            }
        }
        for (auto & [r1,op,r2,ta] : ordered_cmds) {
            if (auto it = replacements.find(r1); it != replacements.end()) { r1 = it->second; changed++; }
            if (auto it = replacements.find(r2); it != replacements.end()) { r2 = it->second; changed++; }
            if (auto it = replacements.find(ta); it != replacements.end()) { ta = it->second; changed++;  }
        }
        std::cout << iter << ' ' << changed << std::endl;
    }

/*
    std::sort(ordered_cmds.begin(), ordered_cmds.end(), [](auto & t1, auto & t2) {
        return std::get<3>(t1) < std::get<3>(t2);
    });

    for (auto & [r1,op,r2,ta] : ordered_cmds) {
        std::cout << r1 << ' ' << op << ' ' << r2 << " -> " << ta;
        std::cout << ' ' << isreg(r1) << ' ' << isreg(r2) << ' ' << isreg(ta);
        std::cout << '\n';
    }
*/

    for (int test = 0 ; false && test <= 44; ++test) {
        for (int comb = 1; comb <= 3; comb++) {
            for (int before = 0; before <= 3; ++before) {
                regs.clear();
                for (int i = 0; i <= 44; i++) {
                    std::string numstr = (i < 10 ? "0" : "") + std::to_string(i);
                    regs["x"+numstr] = (comb & 1 ? i == test : 0);
                    regs["y"+numstr] = (comb & 2 ? i == test : 0);
                }
                for (int i = 1; i <= 45; i++) {
                    std::string numstr = ((i-1) < 10 ? "0" : "") + std::to_string(i-1);
                    regs["x"+numstr] = (before & 1 ? i == test : 0);
                    regs["y"+numstr] = (before & 2 ? i == test : 0);
                }

                std::deque<std::tuple<std::string, std::string, std::string, std::string>> q(cmds.begin(), cmds.end());
                while (!q.empty()) {
                    const auto [r1, cmd, r2, target] = q.front(); q.pop_front();
                    if (regs.find(r1) == regs.end()) { q.emplace_back(r1, cmd, r2, target); continue; }
                    if (regs.find(r2) == regs.end()) { q.emplace_back(r1, cmd, r2, target); continue; }
                    if (cmd == "OR") {
                        regs[target] = regs[r1] | regs[r2];
                    } else if (cmd == "AND") {
                        regs[target] = regs[r1] & regs[r2];
                    } else if (cmd == "XOR") {
                        regs[target] = regs[r1] ^ regs[r2];
                    } else {
                        std::cout << "unknown command: " << cmd << std::endl;
                    }
                }


                uint64_t x = 0, y = 0, z = 0;
                for (auto & [reg,val] : regs) {
                    if (reg[0] == 'z') {
                        auto shift = std::stoll(reg.substr(1));
                        z |= (val << shift);
                    }
                    if (reg[0] == 'y') {
                        auto shift = std::stoll(reg.substr(1));
                        y |= (val << shift);
                    }
                    if (reg[0] == 'x') {
                        auto shift = std::stoll(reg.substr(1));
                        x |= (val << shift);
                    }
                }
                if (x+y != z) {
                    std::cout << test << ' ' << comb << ' ' << before << ' ' << x << "+" << y << "=" << z << ' ' << (x+y==z) << std::endl;
                }
            }
        }
    }
/*
    std::set<std::string> old_lookfor;
    for ( int i = 30 ; i <= 32; ++i ) {
        std::cout << i << ':' << std::endl;
        std::string st = (i < 10 ? "z0" : "z") + std::to_string(i);
        if (regs.find(st) == regs.end()) { break; }
        std::set<std::string> lookfor{st };
        for (auto it = ordered_cmds.rbegin(); it != ordered_cmds.rend(); ++it) {
            const auto & [r1, cmd, r2, target] = *it;
            if (lookfor.find(target) != lookfor.end()) {
                //std::cout << r1 << " " << cmd << " " << r2 << " " << target << std::endl;
                lookfor.emplace(r1);
                lookfor.emplace(r2);
            }
        }
        std::cout << i << ':';
        for (auto & l : lookfor) {
            std::cout << ' ' << l;
        } std::cout << '\n';
        std::vector<std::string> news;
        std::set_difference(lookfor.begin(),lookfor.end(),old_lookfor.begin(),old_lookfor.end(), std::back_inserter(news));
        old_lookfor.swap(lookfor);
        for (auto & s : news) {
            std::cout << ' ' << s;
        } std::cout << '\n';
    }
    */
    std::set<std::string> ss;
    for (auto [a,b] : swaps) {
        ss.insert(a);
        ss.insert(b);
    }

    bool first = true;
    std::ostringstream os;
    for (auto & s : ss) {
        os << (first ? "" : ",") << s;
        first = false;
    }
    ans2 = os.str();

    return {std::to_string(ans1), ans2};
}
