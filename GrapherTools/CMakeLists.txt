set(LIBRARY_NAME GrapherTools)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${LIBRARY_NAME})

set(SOURCES ${SOURCE_DIR}/ScaleFactor.cxx
            ${SOURCE_DIR}/ScaleFactorComponent.cxx
            ${SOURCE_DIR}/ScaleFactorAttributes.cxx
            ${HEADER_DIR}/ScaleFactor.h
            ${HEADER_DIR}/ScaleFactorComponent.h
            ${HEADER_DIR}/ScaleFactorAttributes.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${SOURCE_DIR})

add_library(${LIBRARY_NAME} SHARED ${SOURCES})
target_link_libraries(${LIBRARY_NAME} ${ROOT_LIBRARIES})

set(TEST_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)
add_gtest_test(${LIBRARY_NAME} TestSFAttributes ${TEST_SOURCE_DIR}/ut_ScaleFactorAttributes.cxx)