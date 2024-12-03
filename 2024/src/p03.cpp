#include "aoc.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <set>

std::tuple<std::string, std::string> p03(const std::string &input) {
  int64_t ans1 = 0;
  int64_t ans2 = 0;
  enum class State {
      START, M, MU, MUL, MULPAR, NUM1, NUM1COMMA, NUM2
  };

  std::string cpy = input;

  auto pos = cpy.find("don't()");
  while(pos != std::string::npos) {
    auto end = cpy.find("do()", pos);
    for(size_t i = pos; i < std::min(cpy.size(), end); ++i) {
      cpy[i] = '_';
    }
    pos = cpy.find("don't()", end);
  }

  for(auto p : {1,2}) {

    std::vector<std::tuple<int,int>> v;
    {
      int num1 = 0, num2 = 0;
      State state = State::START;
      bool havenum = false;
      for (const auto c: (p == 1 ? input : cpy)) {
        switch (state) {
          case State::START:
            num1 = num2 = 0;
            if(c=='m') state = State::M; break;
            case State::M: { if (c=='u') state = State::MU; else state=State::START; } break;
            case State::MU: { if (c=='l') state = State::MUL; else state=State::START; } break;
            case State::MUL: { if (c=='(') state = State::MULPAR; else state=State::START; } break;
            case State::MULPAR:
              if (c >= '0' && c <= '9') {num1 = num1*10 + (c-'0'); state = State::NUM1;}
              else state=State::START;
              break;
            case State::NUM1:
              if (c >= '0' && c <= '9') {num1 = num1*10 + (c-'0'); }
              else if(c == ',') state = State::NUM1COMMA;
              else state=State::START;
              break;
            case State::NUM1COMMA:
              if (c >= '0' && c <= '9') {num2 = num2*10 + (c-'0'); state = State::NUM2;}
              else state=State::START;
              break;
            case State::NUM2:
              if (c >= '0' && c <= '9') {num2 = num2*10 + (c-'0');}
              else if(c == ')') { v.emplace_back(num1,num2); state = State::START; }
              else state=State::START;
              break;

        }
      }
    }

    for(auto [a,b]: v) {
      (p == 1? ans1: ans2) += a*b;
    }
  }

  return {std::to_string(ans1), std::to_string(ans2)};
}
