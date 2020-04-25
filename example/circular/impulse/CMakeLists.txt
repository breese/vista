add_executable(circular_impulse_example
  main.cpp
  )

target_link_libraries(circular_impulse_example vista)
add_dependencies(example circular_impulse_example)
