add_executable(sorted_rank_example
  main.cpp
  )

target_link_libraries(sorted_rank_example vista)
add_dependencies(example sorted_rank_example)
