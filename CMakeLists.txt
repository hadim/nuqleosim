cmake_minimum_required(VERSION 2.6)

######################################
## Custom path to QGLViewer and Qwt ##
######################################

## Library and include absolute path needed !!!

set(QGLVIEWER_CUSTOM_PATH
  "/net/stockage/bioinfolib/local32/include"
  "/net/stockage/bioinfolib/local32/lib"
  #"/net/stockage/bioinfolib/local64/include"
  #"/net/stockage/bioinfolib/local64/lib"
)

set(QWT_CUSTOM_PATH
  "/net/stockage/bioinfolib/local32/include"
  "/net/stockage/bioinfolib/local32/lib"
  "/usr/include/qwt-qt4"
  #"/net/stockage/bioinfolib/local64/include"
  #"/net/stockage/bioinfolib/local64/lib"
  )

# Make project title and executable path
project(NuQleoSim)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# Make debug flag compilation
set(CMAKE_BUILD_TYPE Debug)
set(DEBUG ON)

# some CXX flags
add_definitions(-Wall -g)
set(CMAKE_CXX_FLAGS_DEBUG "-O2 -g3")

# Define custom cmake modules path
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/" ${CMAKE_MODULE_PATH})

# Find package
find_package(Qt4 REQUIRED)
find_package(QGLViewer REQUIRED)
find_package(Qwt REQUIRED)

set(QT_USE_QTXML TRUE)
set(QT_USE_QTXMLPATTERNS TRUE)
set(QT_USE_QTNETWORK TRUE)
set(QT_USE_QTOPENGL TRUE)

# Include directory
include(${QT_USE_FILE})
include_directories(${QGLVIEWER_INCLUDE_DIR})
include_directories(${QWT_INCLUDE_DIR})

include_directories(
)

# Source file
file(
  GLOB_RECURSE
  fsrc
  src/*.cpp
  src/*.h
  )

# UI files
file(
  GLOB_RECURSE
  fui
  src/ui/*.ui
  src/visu/*.ui
  src/results/*.ui
  )

# moc files
file(
  GLOB_RECURSE
  fmoc
  src/*.h
  )

# Translation files
file(
  GLOB_RECURSE
  fts
  data/po/*.ts
  )

# Ressource files
file(
  GLOB_RECURSE
  fqrc
  data/*.qrc
  )

# add translations
set(to_trans ${fsrc} ${fui})
qt4_create_translation(wts ${to_trans} ${fts})
#qt4_add_translation(wts ${fts})

# Generate moc files
qt4_automoc(${fsrc})

# Wrap ui files and include them
qt4_wrap_ui(wui ${fui})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# this moc's the above variable and appends to the cxx sources
qt4_wrap_cpp(wmoc ${fmoc})

# Add resources files
qt4_add_resources(wqrc ${fqrc})

# Define executable
add_executable(
  nuqleosim
  ${fsrc}
  ${wui}
  ${wmoc}
  ${wts}
  ${wqrc}
  )

# Add link to libraries
target_link_libraries(
  nuqleosim
  ${QT_LIBRARIES}
  ${QGLVIEWER_LIBRARY}
  ${QWT_LIBRARY}
  )

# Install database and image files
file(GLOB_RECURSE data_files
  "${CMAKE_CURRENT_SOURCE_DIR}/data/db/db.xml"
  "${CMAKE_CURRENT_SOURCE_DIR}/data/db/db.xsd"
  "${CMAKE_CURRENT_SOURCE_DIR}/data/db/db_empty.xml")
install(FILES ${data_files} DESTINATION ${EXECUTABLE_OUTPUT_PATH}/data)

file(GLOB_RECURSE img_files
  "${CMAKE_CURRENT_SOURCE_DIR}/data/db/img/*")
install(FILES ${img_files} DESTINATION ${EXECUTABLE_OUTPUT_PATH}/data/img)

##########################################################
# Generate CPack file to create installation files files #
##########################################################

# set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Wormux - a convivial mass murder game")
# set(CPACK_PACKAGE_NAME "Wormux")
# set(CPACK_PACKAGE_VENDOR "Wormux Development Team")
# #set(CPACK_PACKAGE_DESCRIPTION_FILE "${PROJECT_SOURCE_DIR}/README")
# #set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/COPYING")
# set(CPACK_PACKAGE_VERSION 1.0)
# set(CPACK_PACKAGE_VERSION_MAJOR 1)
# set(CPACK_PACKAGE_VERSION_MINOR 0)
# set(CPACK_PACKAGE_VERSION_PATCH 0)
# set(CPACK_PACKAGE_FILE_NAME ${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION})
# #set(CPACK_PACKAGE_INSTALL_DIRECTORY "Wormux ${WORMUX_MAJOR}.${WORMUX_MINOR}")

# set(CPACK_SOURCE_GENERATOR "TBZ2")

# if(UNIX)
#   set(CPACK_GENERATOR "DEB")
#   set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Hadrien Mary")
#   set(CPACK_PACKAGE_EXECUTABLES "wormux" "Wormux")
#   set(CPACK_STRIP_FILES "bin/wormux")
# endif(UNIX)
# if(WIN32)
#   set(CPACK_GENERATOR "NSIS")
#   set(CPACK_PACKAGE_EXECUTABLES "wormux.exe" "Wormux")
#   # because of a bug in nsis there have to be at least 4 backslashes once
#   set(CPACK_PACKAGE_ICON "${PROJECT_SOURCE_DIR}/data\\\\wormux_32x32.png")
#   set(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.wormux.org")
#   set(CPACK_NSIS_CONTACT "wormux-dev@gna.org")
# endif(WIN32)

# include(CPack)
