###############################################################################
#
# Copyright (C) 2019 Bjorn Reese <breese@users.sourceforge.net>
#
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)
#
###############################################################################

include(GoogleBenchmark.cmake)

add_custom_target(benchmark)

function(vista_add_benchmark name)
  add_executable(${name} ${ARGN})
  target_link_libraries(${name} vista Google::benchmark)
  target_compile_options(${name} PRIVATE ${VISTA_WARNING_FLAGS} -DNDEBUG=1)
  add_dependencies(benchmark ${name})
endfunction()

vista_add_benchmark(circular_view_benchmark circular_view_benchmark.cpp)

vista_add_benchmark(algorithm_benchmark algorithm_benchmark.cpp)
vista_add_benchmark(std_algorithm_benchmark std_algorithm_benchmark.cpp)
