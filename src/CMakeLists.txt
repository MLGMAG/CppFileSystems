# Hard link search Unix
include_directories(${SOURCE_PATH}/hardLinkSearchUnix)
add_library(
        hardLinkSearcherLib STATIC
        ${SOURCE_PATH}/hardLinkSearchUnix/hardLinkSearcher.h
        ${SOURCE_PATH}/hardLinkSearchUnix/hardLinkSearcher.cpp
)
add_executable(hardLinkSearchUnix hardLinkSearchUnix/hardLinkSearch.cpp)
target_link_libraries(hardLinkSearchUnix hardLinkSearcherLib)

# Directory traversal Unix
include_directories(${SOURCE_PATH}/directoryTraversalUnix)
add_library(
        directoryTraverserUnixLib STATIC
        ${SOURCE_PATH}/directoryTraversalUnix/directoryTraverser.h
        ${SOURCE_PATH}/directoryTraversalUnix/directoryTraverser.cpp
)
add_executable(directoryTraverserUnix directoryTraversalUnix/directoryTraverser.h directoryTraversalUnix/directoryTraverser.cpp)
add_executable(directoryTraversalUnix directoryTraversalUnix/directoryTraversal.cpp)
target_link_libraries(directoryTraversalUnix directoryTraverserUnixLib)

# Disk info Win
add_executable(diskInfoWin diskInfoWin/diskInfo.cpp)

# Directory traversal Win
add_executable(directoryTraversalWin directoryTraversalWin/directoryTraversal.cpp)
