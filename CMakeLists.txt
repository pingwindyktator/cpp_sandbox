cmake_minimum_required(VERSION 3.8)

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "Do not build in-source. Please remove CMakeCache.txt and the CMakeFiles/ directory. Then build out-of-source.")
endif()

find_package(Boost COMPONENTS filesystem system program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wcast-align -Wcast-qual -Wstrict-aliasing -O2                     \
                     -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wnon-virtual-dtor            \
                     -Wold-style-cast -Woverloaded-virtual -Wredundant-decls                                             \
                     -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wundef -Werror -Wno-unused")

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${Boost_LIBRARIES} pthread)
