###############################################################################
#
# Copyright (C) 2019 Bjorn Reese <breese@users.sourceforge.net>
#
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)
#
###############################################################################

cmake_minimum_required(VERSION 3.7)
project(vista)

get_filename_component(VISTA_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../" ABSOLUTE)
if (NOT DEFINED VISTA_BUILD_DIR)
  set(VISTA_BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR})
endif()
set(LIBRARY_OUTPUT_PATH ${VISTA_BUILD_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${VISTA_BUILD_DIR}/bin)

# Require at least C++11
if (${CMAKE_VERSION} VERSION_LESS 3.8)
  set(VISTA_FEATURES cxx_auto_type)
else()
  set(VISTA_FEATURES cxx_std_11)
endif()

###############################################################################
# Vista
###############################################################################

add_library(vista INTERFACE)

set_target_properties(vista PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${VISTA_ROOT}/include"
  INTERFACE_COMPILE_FEATURES "${VISTA_FEATURES}")

install(DIRECTORY ${VISTA_ROOT}/include
  DESTINATION .
  FILES_MATCHING PATTERN "*.[hi]pp"
  )
