
#.rst:
# FindGTestLocal
# --------
#
# Find gtest
#
# Find the gtest libraries 
#
# ::
#
#   This module defines the following variables:
#      GTEST_FOUND       - True if GTEST_INCLUDE_DIR & GTEST_LIBRARY are found
#      GTEST_INCLUDE_DIR   - Set when GTEST_FOUND true
#      GMOCK_INCLUDE_DIR  - Set when GTEST_FOUND true
#
#
find_path(GTEST_INCLUDE_DIR NAMES ./modules/googletest/include/gtest/gtest
          DOC "GTest headers"
)

find_library(GTEST_LIBRARY NAMES ./modules/googletest/googlemock/gtest/libgtest
          DOC "GTest library"
)

find_path(GMOCK_INCLUDE_DIR NAMES ./modules/googletest/include/gmock/gmock
          DOC "GMock headers"
)

find_library(GMOCK_LIBRARY NAMES ./modules/googletest/googlemock/libgmock
          DOC "GMock library"
)

set(CMAKE_DIR /usr/local/share/cmake-3.8/Modules)

include(${CMAKE_DIR}/FindPackageHandleStandardArgs.cmake)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GTEST
                                  REQUIRED_VARS GTEST_LIBRARY GTEST_INCLUDE_DIR)

if(GTEST_FOUND)
  set( GTEST_LIBRARIES ${GTEST_LIBRARY} )
  set( GMOCK_LIBRARIES ${GMOCK_LIBRARY} )
  set( GTEST_INCLUDE_DIRS ${GTEST_INCLUDE_DIR} )
  set( GMOCK_INCLUDE_DIRS ${GMOCK_INCLUDE_DIR} )
endif()

mark_as_advanced(GMOCK_INCLUDE_DIR GMOCK_LIBRARY)
mark_as_advanced(GTEST_INCLUDE_DIR GTEST_LIBRARY)