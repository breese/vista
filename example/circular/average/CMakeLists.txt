add_executable(circular_average_example
  main.cpp
  )

target_link_libraries(circular_average_example vista)
add_dependencies(example circular_average_example)
