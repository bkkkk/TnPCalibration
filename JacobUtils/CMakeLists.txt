set(LIBRARY_NAME JacobUtils)
set(LIBRARY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(LIBRARY_HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${LIBRARY_NAME})
set(TEST_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

set(LIBRARY_SOURCES ${LIBRARY_SOURCE_DIR}/LoggingUtility.cxx
                    ${LIBRARY_SOURCE_DIR}/MathTools.cxx
                    ${LIBRARY_SOURCE_DIR}/ReaderTools.cxx
                    ${LIBRARY_SOURCE_DIR}/SampleList.cxx
                    ${LIBRARY_HEADER_DIR}/LoggingUtility.h
                    ${LIBRARY_HEADER_DIR}/LoggingUtilityMacros.h
                    ${LIBRARY_HEADER_DIR}/MathTools.h
                    ${LIBRARY_HEADER_DIR}/ReaderTools.h
                    ${LIBRARY_HEADER_DIR}/SampleList.h
                    ${LIBRARY_HEADER_DIR}/StringUtils.h
                    ${LIBRARY_HEADER_DIR}/Uncopyable.h
                    ${LIBRARY_HEADER_DIR}/VectorUtils.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${GTest_INCLUDE_DIR})

add_library(${LIBRARY_NAME} SHARED ${LIBRARY_SOURCES})
target_link_libraries(${LIBRARY_NAME} ${ROOT_LIBRARIES})

add_gtest_test(${LIBRARY_NAME} TestLoggingUtility ${TEST_SOURCE_DIR}/ut_LoggingUtility.cxx)
add_gtest_test(${LIBRARY_NAME} TestReaderTools ${TEST_SOURCE_DIR}/ut_ReaderTools.cxx)
add_gtest_test(${LIBRARY_NAME} TestSampleList ${TEST_SOURCE_DIR}/ut_SampleList.cxx)