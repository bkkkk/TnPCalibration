set(LIBRARY_NAME TruthNavigationTools)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${LIBRARY_NAME})
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

set(LIBRARY_SOURCES ${SOURCE_DIR}/ChainNavigationTools.cxx
                    ${SOURCE_DIR}/TruthMuonMatching.cxx
                    ${SOURCE_DIR}/TruthTools.cxx
                    ${HEADER_DIR}/ChainNavigationTools.h
                    ${HEADER_DIR}/TruthEnums.h
                    ${HEADER_DIR}/TruthMuonMatching.h
                    ${HEADER_DIR}/TruthTools.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/D3PDReaderAdapter/)
include_directories(${PROJECT_SOURCE_DIR}/JacobUtils/)
include_directories(${PROJECT_SOURCE_DIR}/TnPSelector/)

add_library(${LIBRARY_NAME} SHARED ${LIBRARY_SOURCES})
target_link_libraries(${LIBRARY_NAME} ${ROOT_LIBRARIES})
target_link_libraries(${LIBRARY_NAME} TnPSelector)

add_gtest_test(${LIBRARY_NAME} TestTruthTools ${TEST_DIR}/ut_TruthTools.cxx)
