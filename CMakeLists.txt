cmake_minimum_required(VERSION 3.1.0)
project(Convex_hull CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CGAL_DO_NOT_WARN_ABOUT_CMAKE_BUILD_TYPE TRUE)

find_package(CGAL REQUIRED)
include(${CGAL_USE_FILE})

if (WIN32)
    set(Qt5_DIR_PATH_TEMP "C:\Qt\5.11.0\msvc2015_64\lib\cmake\Qt5")
else()
    if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        set(Qt5_DIR_PATH_TEMP "/usr/local/opt/qt5/lib/cmake/Qt5")
    elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin") # Mac OS X
        set(Qt5_DIR_PATH_TEMP "/usr/local/Cellar/qt/5.11.2/lib/cmake/Qt5")
    else()
        set(Qt5_DIR_PATH_TEMP "/usr/local/opt/qt5/lib/cmake/Qt5")
    endif()
endif()

set(Qt5_DIR_PATH "${Qt5_DIR_PATH_TEMP}" CACHE PATH "Path to Qt5 cmake files")
set(Qt5_DIR ${Qt5_DIR_PATH})

# Find includes in corresponding build directories
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
#set(CMAKE_AUTOMOC ON)

find_package(Qt5 CONFIG REQUIRED Widgets Xml OpenGL)

set(QGLVIEWER_LIB_DIR "${CMAKE_SOURCE_DIR}/../libQGLViewer-2.7.1/QGLViewer/" CACHE PATH "Path to QGLViewer library")
find_library(QGLVIEWER_LIB NAMES ${CMAKE_SHARED_LIBRARY_PREFIX}QGLViewer${CMAKE_SHARED_LIBRARY_SUFFIX} HINTS ${QGLVIEWER_LIB_DIR} PATHS ${QGLVIEWER_LIB_DIR})

set(QGLVIEWER_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../libQGLViewer-2.7.1/QGLViewer/" CACHE PATH "Path to QGLViewer include files")

find_package(OpenGL REQUIRED)
#find_package(QGLViewer REQUIRED)

set(SOURCES main.cpp Viewer.cpp)
set(HEADERS Viewer.h)

add_executable(Convex_hull ${SOURCES} ${HEADERS})
target_link_libraries(Convex_hull
    PRIVATE
    ${CGAL_LIBS}
    Qt5::Widgets Qt5::Xml Qt5::OpenGL
    ${QGLVIEWER_LIB}
    ${OPENGL_LIBRARIES}
)
target_include_directories(Convex_hull PUBLIC ${OPENGL_INCLUDE_DIR} ${QGLVIEWER_INCLUDE_DIR})
