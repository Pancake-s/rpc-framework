find_package(protobuf)

add_custom_command(
  OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/../caller/user.pb.cc"
         "${CMAKE_CURRENT_SOURCE_DIR}/../caller/user.pb.h"
  DEPENDS protoc "../caller/user.proto"
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMAND ${CMAKE_BINARY_DIR}/output/protoc -I=../caller --cpp_out=../caller ../caller/user.proto
  COMMENT "Running C++ protocol buffer compiler on user.proto"
  VERBATIM
)

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