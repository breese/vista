# ring_span requires C++14

if ("cxx_std_14" IN_LIST CMAKE_CXX_COMPILE_FEATURES)
  add_executable(circular_p0059_example
    main.cpp
    )

  target_compile_features(circular_p0059_example PUBLIC cxx_std_14)
  target_link_libraries(circular_p0059_example vista)
  add_dependencies(example circular_p0059_example)
else()
  message("Skipping p0059 example")
endif()
