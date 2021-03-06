cmake_minimum_required(VERSION 3.1.0)
project(QtCGAL3DViewer CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
if(MSVC)
    add_compile_options("/W3")
else()
    add_compile_options("-Wall")
endif()

set(CGAL_DO_NOT_WARN_ABOUT_CMAKE_BUILD_TYPE TRUE)

find_package(CGAL COMPONENTS Core ImageIO Qt5 REQUIRED)
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
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 CONFIG REQUIRED Widgets Xml OpenGL)

set(QGLVIEWER_LIB_DIR "${CMAKE_SOURCE_DIR}/../libQGLViewer-2.7.1/QGLViewer/" CACHE PATH "Path to QGLViewer library")
#find_library(QGLVIEWER_LIBRARIES NAMES ${CMAKE_SHARED_LIBRARY_PREFIX}QGLViewer${CMAKE_SHARED_LIBRARY_SUFFIX} HINTS ${QGLVIEWER_LIB_DIR} PATHS ${QGLVIEWER_LIB_DIR})
#if ($(QGLVIEWER_LIBRARIES) MATCHES "QGLVIEWER_LIBRARIES-NOTFOUND")
    find_library(QGLVIEWER_LIBRARIES NAMES libQGLViewer-qt5.so HINTS ${QGLVIEWER_LIB_DIR} PATHS ${QGLVIEWER_LIB_DIR})
#endif()
set(QGLVIEWER_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../libQGLViewer-2.7.1/" CACHE PATH "Path to QGLViewer include files")

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
#find_package(QGLViewer REQUIRED)

find_package(OpenGL REQUIRED)

set(SOURCES main.cpp Viewer3D.cpp MainWindow.cpp BSpline.cpp PNtriangle.cpp DrawingElements.cpp SubdivisionCurve.cpp Mesh3Triangulation.cpp)
set(HEADERS Viewer3D.h MainWindow.h BSpline.h PNtriangle.h DrawingElements.h SubdivisionCurve.h Mesh3Triangulation.h typedefs.h)
qt5_wrap_ui(UI_HEADERS mainwindow.ui)

add_executable(QtCGAL3DViewer ${SOURCES} ${HEADERS} ${UI_HEADERS})
target_link_libraries(QtCGAL3DViewer
    PRIVATE
    ${CGAL_LIBS}
    Qt5::Widgets Qt5::Xml Qt5::OpenGL
    ${QGLVIEWER_LIBRARIES}
    ${OPENGL_LIBRARIES}
)
target_include_directories(QtCGAL3DViewer PUBLIC ${OPENGL_INCLUDE_DIR} ${QGLVIEWER_INCLUDE_DIR})
