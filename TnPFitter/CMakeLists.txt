set(LIBRARY_NAME TnPFitter)

set(SOURCE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

file(GLOB PROJECT1_SRCS ${SOURCE_DIRS}/*.cxx)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/TnPFitter/)
include_directories(${PROJECT_SOURCE_DIR}/RootAdapters/)
include_directories(${PROJECT_SOURCE_DIR}/JacobUtils/)

add_library(${LIBRARY_NAME} SHARED ${PROJECT1_SRCS})
target_link_libraries(${LIBRARY_NAME} ${ROOT_LIBRARIES})
target_link_libraries(${LIBRARY_NAME} RootAdapters)

add_gtest_test(${LIBRARY_NAME} TestFitConfig ${TEST_DIR}/ut_FitConfig.cxx)
add_gtest_test(${LIBRARY_NAME} TestSingleGaus ${TEST_DIR}/ut_SingleGausFit.cxx)
