find_package(Protobuf)

add_executable(provider
  userservice.cc
  ../caller/user.pb.cc
)

target_include_directories(provider
  PRIVATE ../caller
)

target_link_libraries(provider
  PRIVATE protobuf::libprotobuf
  PRIVATE mprpc::mprpc
)