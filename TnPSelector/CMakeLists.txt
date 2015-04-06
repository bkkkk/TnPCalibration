set(LIBRARY_NAME TnPSelector)
set(LIBRARY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

set(LIBRARY_SOURCES ${LIBRARY_SOURCE_DIR}/KinematicUtils.cxx
    ${LIBRARY_SOURCE_DIR}/PrintUtils.cxx
    ${LIBRARY_SOURCE_DIR}/TJPsiClassifier.cxx
    ${LIBRARY_SOURCE_DIR}/TJPsiMCPSelector.cxx
    ${LIBRARY_SOURCE_DIR}/TJPsiMuonProbeSelector.cxx
    ${LIBRARY_SOURCE_DIR}/TJPsiPairSelector.cxx
    ${LIBRARY_SOURCE_DIR}/TJPsiProbeSelector.cxx
    ${LIBRARY_SOURCE_DIR}/TJPsiSMTSelector.cxx
    ${LIBRARY_SOURCE_DIR}/TJPsiTagSelector.cxx
    ${LIBRARY_SOURCE_DIR}/TTriggerMatching.cxx)

include_directories("./")
include_directories(${PROJECT_SOURCE_DIR}/D3PDReaderAdapter/)
include_directories(${PROJECT_SOURCE_DIR}/JacobUtils/)
include_directories(${GTest_INCLUDE_DIR})

# Compile library file
add_library(${LIBRARY_NAME} SHARED ${LIBRARY_SOURCES})
target_link_libraries(${LIBRARY_NAME} ${ROOT_LIBRARIES})

# Testing
add_gtest_test(${LIBRARY_NAME} TestClassifier ${TEST_SOURCE_DIR}/ut_Classifier.cxx)
add_gtest_test(${LIBRARY_NAME} TestKinematicUtils ${TEST_SOURCE_DIR}/ut_KinematicUtils.cxx)
add_gtest_test(${LIBRARY_NAME} TestMuonProbeSelector ${TEST_SOURCE_DIR}/ut_MuonProbeSelector.cxx)
add_gtest_test(${LIBRARY_NAME} TestPairSelector ${TEST_SOURCE_DIR}/ut_PairSelector.cxx)
add_gtest_test(${LIBRARY_NAME} TestProbeSelector ${TEST_SOURCE_DIR}/ut_ProbeSelector.cxx)
add_gtest_test(${LIBRARY_NAME} TestSMTSelector ${TEST_SOURCE_DIR}/ut_SMTSelector.cxx)
add_gtest_test(${LIBRARY_NAME} TestTagSelector ${TEST_SOURCE_DIR}/ut_TagSelector.cxx)