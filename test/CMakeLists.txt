###############################################################################
#
# Copyright (C) 2019 Bjorn Reese <breese@users.sourceforge.net>
#
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)
#
###############################################################################

# Boost.Core/Detail (lightweight_test)
find_package(Boost 1.57.0 QUIET)

function(vista_add_test name)
  add_executable(${name} ${ARGN})
  target_include_directories(${name} SYSTEM PRIVATE "${Boost_INCLUDE_DIRS}")
  target_link_libraries(${name} vista)
  add_test(${name} ${EXECUTABLE_OUTPUT_PATH}/${name})
endfunction()

vista_add_test(span_suite span_suite.cpp)
