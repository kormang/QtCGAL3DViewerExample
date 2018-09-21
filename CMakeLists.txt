cmake_minimum_required(VERSION 3.0)
project(Convex_hull CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CGAL_DO_NOT_WARN_ABOUT_CMAKE_BUILD_TYPE TRUE)
find_package(CGAL REQUIRED)
include(${CGAL_USE_FILE})

set(SOURCES main.cpp)

add_executable(Convex_hull ${SOURCES})
target_link_libraries(Convex_hull ${CGAL_LIBS})
