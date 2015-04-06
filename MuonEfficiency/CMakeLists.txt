set(LIBRARY_NAME MuonEfficiency)

# Setup folder structure
set(SOURCE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

file(GLOB PROJECT1_SRCS ${SOURCE_DIRS}/*.cxx)

# Includes
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(${LIBRARY_NAME} SHARED ${PROJECT1_SRCS})
target_link_libraries(${LIBRARY_NAME} ${ROOT_LIBRARIES})