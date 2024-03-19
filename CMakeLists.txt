cmake_minimum_required(VERSION 3.5)

project(LeetCode LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SRC_FILES "*/*.cpp")

add_executable(LeetCode ${SRC_FILES})

include(GNUInstallDirs)
install(TARGETS LeetCode
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
