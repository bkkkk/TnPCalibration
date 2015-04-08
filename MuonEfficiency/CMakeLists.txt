set(LIBRARY_NAME MuonEfficiency)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${LIBRARY_NAME})
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

set(LIBRARY_SOURCES ${HEADER_DIR}/EfficiencyMaker.h
                    ${HEADER_DIR}/EventWeighting.h
                    ${HEADER_DIR}/FitResults.h
                    ${HEADER_DIR}/HistogramCollector.h
                    ${HEADER_DIR}/HistogramFactory.h
                    ${HEADER_DIR}/PileupPRW.h
                    ${HEADER_DIR}/PileupReWeighting.h
                    ${HEADER_DIR}/SampleHistograms.h
                    ${HEADER_DIR}/ScaleFactorMaker.h
                    ${HEADER_DIR}/ScaleFactorPlotter.h
                    ${HEADER_DIR}/SingleGausFit.h
                    ${HEADER_DIR}/SliceHisto.h
                    ${HEADER_DIR}/SummaryPlotMaker.h
                    ${HEADER_DIR}/TnPSlices.h
                    ${HEADER_DIR}/Weighting.h
                    ${SOURCE_DIR}/EfficiencyMaker.cxx
                    ${SOURCE_DIR}/EventWeighting.cxx
                    ${SOURCE_DIR}/FitResults.cxx
                    ${SOURCE_DIR}/HistogramCollector.cxx
                    ${SOURCE_DIR}/HistogramFactory.cxx
                    ${SOURCE_DIR}/PileupPRW.cxx
                    ${SOURCE_DIR}/PileupReWeighting.cxx
                    ${SOURCE_DIR}/SampleHistograms.cxx
                    ${SOURCE_DIR}/ScaleFactorPlotter.cxx
                    ${SOURCE_DIR}/SingleGausFit.cxx
                    ${SOURCE_DIR}/SliceHisto.cxx
                    ${SOURCE_DIR}/SummaryPlotMaker.cxx
                    ${SOURCE_DIR}/TnPSlices.cxx)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/D3PDReaderAdapter/)
include_directories(${PROJECT_SOURCE_DIR}/JacobUtils/)
include_directories(${PROJECT_SOURCE_DIR}/TnPSelector/)

add_library(${LIBRARY_NAME} SHARED ${LIBRARY_SOURCES})
target_link_libraries(${LIBRARY_NAME} ${ROOT_LIBRARIES})

add_gtest_test(${LIBRARY_NAME} TestHistogramCollector ${TEST_DIR}/ut_HistogramCollector.cxx)
add_gtest_test(${LIBRARY_NAME} TestScaleFactorPlotter ${TEST_DIR}/ut_ScaleFactorPlotter.cxx)
add_gtest_test(${LIBRARY_NAME} TestSingleGausFit ${TEST_DIR}/ut_SingleGausFit.cxx)