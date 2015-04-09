set(LIBRARY_NAME TnPFitter)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)
set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${LIBRARY_NAME})

set(LIBRARY_SOURCES ${HEADER_DIR}/CompositeFunction.h
                    ${HEADER_DIR}/DoubleGausFit.h
                    ${HEADER_DIR}/FitConfig.h
                    ${HEADER_DIR}/FitDrawingHelpers.h
                    ${HEADER_DIR}/FitEfficiency.h
                    ${HEADER_DIR}/FitIntegral.h
                    ${HEADER_DIR}/FitResult.h
                    ${HEADER_DIR}/FitScaleFactor.h
                    ${HEADER_DIR}/FittableFunction.h
                    ${HEADER_DIR}/FittableGroup.h
                    ${HEADER_DIR}/FitterDraw.h
                    ${HEADER_DIR}/IFitter.h
                    ${HEADER_DIR}/SingleGausFit.h
                    ${SOURCE_DIR}/CompositeFunction.cxx
                    ${SOURCE_DIR}/DoubleGausFit.cxx
                    ${SOURCE_DIR}/FitConfig.cxx
                    ${SOURCE_DIR}/FitDrawingHelpers.cxx
                    ${SOURCE_DIR}/FitEfficiency.cxx
                    ${SOURCE_DIR}/FitIntegral.cxx
                    ${SOURCE_DIR}/FitResult.cxx
                    ${SOURCE_DIR}/FitScaleFactor.cxx
                    ${SOURCE_DIR}/FittableFunction.cxx
                    ${SOURCE_DIR}/FittableGroup.cxx
                    ${SOURCE_DIR}/FitterDraw.cxx
                    ${SOURCE_DIR}/IFitter.cxx
                    ${SOURCE_DIR}/SingleGausFit.cxx)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/RootAdapters/)
include_directories(${PROJECT_SOURCE_DIR}/JacobUtils/)

add_library(${LIBRARY_NAME} SHARED ${LIBRARY_SOURCES})
target_link_libraries(${LIBRARY_NAME} ${ROOT_LIBRARIES})
target_link_libraries(${LIBRARY_NAME} RootAdapters)

add_gtest_test(${LIBRARY_NAME} TestFitConfig ${TEST_DIR}/ut_FitConfig.cxx)
add_gtest_test(${LIBRARY_NAME} TestSingleGaus ${TEST_DIR}/ut_SingleGausFit.cxx)
