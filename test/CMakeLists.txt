find_package(Protobuf)

add_executable(test
  main.cc
  test.pb.cc)

target_link_libraries(test
  protobuf::libprotobuf
)
