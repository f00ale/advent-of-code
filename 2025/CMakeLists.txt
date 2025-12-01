cmake_minimum_required(VERSION 3.18)
project(aoc25)

set(CMAKE_CXX_STANDARD 17)

if(${SANITIZE})
add_compile_options(-fsanitize=address,leak)
add_link_options(-fsanitize=address,leak)
endif()

add_compile_options(-Wall -Wextra -march=native)

add_library(aoc25_problems OBJECT
        src/p01.cpp
#        src/p02.cpp
#        src/p03.cpp
#        src/p04.cpp
#        src/p05.cpp
#        src/p06.cpp
#        src/p07.cpp
#        src/p08.cpp
#        src/p09.cpp
#        src/p10.cpp
#        src/p11.cpp
#        src/p12.cpp
        )

add_executable(aoc25 src/main.cpp)
target_link_libraries(aoc25 PRIVATE aoc25_problems)
