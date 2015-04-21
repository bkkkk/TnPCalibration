cmake_minimum_required(VERSION 3.2)
project(TnPCalibration CXX)

# Add ROOT Framework
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED COMPONENTS MathCore RIO Hist Tree Net Physics Core Graf Graf3d Gpad Rint Postscript Matrix Thread)
include_directories(${CMAKE_SOURCE_DIR} ${ROOT_INCLUDE_DIRS})
add_definitions(${ROOT_CXX_FLAGS})
add_definitions(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wcast-align -Wunused -Woverloaded-virtual)
add_definitions(-pedantic-errors -Werror)
set_property(GLOBAL PROPERTY CXX_STANDARD 11)
set_property(GLOBAL PROPERTY CXX_STANDARD_REQUIRED ON)

# Import Google Test framework
include_directories("/usr/local/gmock/gtest/include")
add_library(gtest STATIC IMPORTED)
set_property(TARGET gtest PROPERTY IMPORTED_LOCATION "/usr/local/gmock/build/libmock.a")

enable_testing()

function(add_gtest_test library_under_test target)
  add_executable(${target} ${ARGN})
  target_link_libraries(${target} gtest)
  target_link_libraries(${target} ${library_under_test})

  add_test(${target} ${target})
endfunction()

add_subdirectory(RootAdapters)
add_subdirectory(TnPFitter)
add_subdirectory(TnPSelector)
add_subdirectory(TruthNavigationTools)
add_subdirectory(GrapherTools)
add_subdirectory(JacobUtils)
add_subdirectory(PhysicsTools)
