find_package(Boost)

add_executable(test_boost main.cc)

target_link_libraries(test_boost
  PRIVATE Boost::boost
)