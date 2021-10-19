# Hard link search Unix
include_directories(${SOURCE_PATH}/hardLinkSearchUnix)
add_library(
        hardLinkSearcherLib STATIC
        ${SOURCE_PATH}/hardLinkSearchUnix/hardLinkSearcher.h
        ${SOURCE_PATH}/hardLinkSearchUnix/hardLinkSearcher.cpp
)
add_executable(hardLinkSearchUnix hardLinkSearchUnix/hardLinkSearch.cpp)
target_link_libraries(hardLinkSearchUnix hardLinkSearcherLib)
