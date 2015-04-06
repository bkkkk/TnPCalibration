set(ROOTADAPTERS_INCLUDES "RootAdapters")
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(ROOTADAPTERS_SRCS "src/SmartFunction.cxx")
add_library(RootAdapters STATIC ${ROOTADAPTERS_SRCS})
