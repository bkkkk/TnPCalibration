set(LIBRARY_NAME MuonEfficiency)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${LIBRARY_NAME})
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)

set(LIBRARY_SOURCES ${SOURCE_DIR}/EfficiencyMaker.cxx ${HEADER_DIR}/EfficiencyMaker.h
                    ${SOURCE_DIR}/EventWeighting.cxx ${HEADER_DIR}/EventWeighting.h
                    ${SOURCE_DIR}/FitResults.cxx ${HEADER_DIR}/FitResults.h
                    ${SOURCE_DIR}/HistogramCollector.cxx ${HEADER_DIR}/HistogramCollector.h
                    # ${SOURCE_DIR}/HistogramFactory.cxx ${HEADER_DIR}/HistogramFactory.h
                    # ${SOURCE_DIR}/PileupPRW.cxx ${HEADER_DIR}/PileupPRW.h
                    ${SOURCE_DIR}/PileupReWeighting.cxx ${HEADER_DIR}/PileupReWeighting.h
                    ${SOURCE_DIR}/SampleHistograms.cxx ${HEADER_DIR}/SampleHistograms.h
                    ${HEADER_DIR}/ScaleFactorMaker.h
                    ${SOURCE_DIR}/ScaleFactorPlotter.cxx ${HEADER_DIR}/ScaleFactorPlotter.h
                    ${SOURCE_DIR}/SingleGausFit.cxx ${HEADER_DIR}/SingleGausFit.h
                    ${SOURCE_DIR}/SliceHisto.cxx ${HEADER_DIR}/SliceHisto.h
                    ${SOURCE_DIR}/SummaryPlotMaker.cxx ${HEADER_DIR}/SummaryPlotMaker.h
                    ${SOURCE_DIR}/TnPSlices.cxx ${HEADER_DIR}/TnPSlices.h
                    ${HEADER_DIR}/Weighting.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/D3PDReaderAdapter/)
include_directories(${PROJECT_SOURCE_DIR}/JacobUtils/)
include_directories(${PROJECT_SOURCE_DIR}/TnPSelector/)

add_library(${LIBRARY_NAME} SHARED ${LIBRARY_SOURCES})
target_link_libraries(${LIBRARY_NAME} ${ROOT_LIBRARIES})

add_gtest_test(${LIBRARY_NAME} TestHistogramCollector ${TEST_DIR}/ut_HistogramCollector.cxx)
add_gtest_test(${LIBRARY_NAME} TestScaleFactorPlotter ${TEST_DIR}/ut_ScaleFactorPlotter.cxx)
add_gtest_test(${LIBRARY_NAME} TestSingleGausFit ${TEST_DIR}/ut_SingleGausFit.cxx)