set(LIBRARY_NAME TnPSelector)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${LIBRARY_NAME})
set(TEST_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

set(LIBRARY_SOURCES ${SOURCE_DIR}/KinematicUtils.cxx
    ${SOURCE_DIR}/PrintUtils.cxx
    ${SOURCE_DIR}/TJPsiClassifier.cxx
    ${SOURCE_DIR}/TJPsiMCPSelector.cxx
    ${SOURCE_DIR}/TJPsiMuonProbeSelector.cxx
    ${SOURCE_DIR}/TJPsiPairSelector.cxx
    ${SOURCE_DIR}/TJPsiProbeSelector.cxx
    ${SOURCE_DIR}/TJPsiSMTSelector.cxx
    ${SOURCE_DIR}/TJPsiTagSelector.cxx
    ${SOURCE_DIR}/TTriggerMatching.cxx
    ${HEADER_DIR}/CutflowCollector.h
    ${HEADER_DIR}/KinematicUtils.h
    ${HEADER_DIR}/PrintUtils.h
    ${HEADER_DIR}/TJPsiClassifier.h
    ${HEADER_DIR}/TJPsiMuonProbeSelector.h
    ${HEADER_DIR}/TJPsiPairSelector.h
    ${HEADER_DIR}/TJPsiProbeSelector.h
    ${HEADER_DIR}/TJPsiSMTSelector.h
    ${HEADER_DIR}/TJPsiTagSelector.h
    ${HEADER_DIR}/TMCPSelector.h
    ${HEADER_DIR}/TTriggerMatching.h)

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