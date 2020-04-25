find_package(Threads)

add_executable(circular_concurrent_example
  main.cpp
  )

target_link_libraries(circular_concurrent_example vista Threads::Threads)
add_dependencies(example circular_concurrent_example)
