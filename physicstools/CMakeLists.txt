cmake_minimum_required(VERSION 3.2)

include_directories("./")

add_executable(testMatchResult test/ut_MatchResult.cpp)
target_link_libraries(testMatchResult gtest)
add_test(testMatchResult testMatchResult)
