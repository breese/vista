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
vista_add_test(span_constexpr_suite span_constexpr_suite.cpp)

vista_add_test(circular_span_suite circular/span_suite.cpp)
vista_add_test(circular_span_iterator_suite circular/span_iterator_suite.cpp)
vista_add_test(circular_span_segment_suite circular/span_segment_suite.cpp)
vista_add_test(circular_span_algorithm_suite circular/span_algorithm_suite.cpp)
vista_add_test(circular_span_numeric_suite circular/span_numeric_suite.cpp)
vista_add_test(circular_array_suite circular/array_suite.cpp)
vista_add_test(circular_array_numeric_suite circular/array_numeric_suite.cpp)

vista_add_test(sorted_algorithm_suite sorted/algorithm_suite.cpp)
vista_add_test(sorted_span_suite sorted/span_suite.cpp)

vista_add_test(heap_algorithm_suite heap/algorithm_suite.cpp)
vista_add_test(priority_span_suite priority/span_suite.cpp)

vista_add_test(map_array_suite map/array_suite.cpp)
