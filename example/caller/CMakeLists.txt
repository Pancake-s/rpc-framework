find_package(protobuf)

add_executable(consumer
  calluserservice.cc
  user.pb.cc
)

target_link_libraries(consumer
  PRIVATE protobuf::libprotobuf
  PRIVATE mprpc::mprpc
)