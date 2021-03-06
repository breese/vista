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

function(vista_add_compile_test name)
  add_library(${name} ${ARGN})
  target_include_directories(${name} SYSTEM PRIVATE "${Boost_INCLUDE_DIRS}")
  target_link_libraries(${name} vista)
endfunction()

vista_add_test(algorithm_suite algorithm_suite.cpp)
vista_add_test(funtional_suite functional_suite.cpp)
vista_add_compile_test(funtional_constexpr_suite functional_constexpr_suite.cpp)
vista_add_test(utility_suite utility_suite.cpp)
vista_add_compile_test(utility_constexpr_suite utility_constexpr_suite.cpp)

vista_add_test(span_suite span_suite.cpp)
vista_add_test(span_constexpr_suite span_constexpr_suite.cpp)

vista_add_test(circular_view_suite circular_view_suite.cpp)
vista_add_test(circular_view_algorithm_suite circular_view_algorithm_suite.cpp)
vista_add_test(circular_view_iterator_suite circular_view_iterator_suite.cpp)
vista_add_test(circular_view_numeric_suite circular_view_numeric_suite.cpp)
vista_add_test(circular_view_segment_suite circular_view_segment_suite.cpp)

vista_add_test(circular_array_suite circular_array_suite.cpp)
vista_add_test(circular_array_numeric_suite circular_array_numeric_suite.cpp)

vista_add_test(priority_view_suite priority_view_suite.cpp)

vista_add_test(map_view_suite map_view_suite.cpp)
vista_add_test(map_array_suite map_array_suite.cpp)
vista_add_test(constant_map_suite constant_map_suite.cpp)

if ("cxx_std_14" IN_LIST CMAKE_CXX_COMPILE_FEATURES)

  vista_add_compile_test(algorithm_constexpr_suite algorithm_constexpr_suite.cpp)
  target_compile_features(algorithm_constexpr_suite PRIVATE cxx_std_14)

  vista_add_compile_test(constant_map_constexpr_suite constant_map_constexpr_suite.cpp)
  target_compile_features(constant_map_constexpr_suite PRIVATE cxx_std_14)

else()
  message("Skipping C++14 test suites")
endif()
