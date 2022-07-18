find_package(protobuf REQUIRED)

set(PROTO_SRCS "")
set(PROTO_HEADERS "")

# # for each .proto file
# get_filename_component(PROTO_NAME test.proto NAME_WE)
# list(APPEND PROTO_SRCS "${PROTO_NAME}.pb.cc")
# list(APPEND PROTO_HEADERS "${PROTO_NAME}.pb.h")

# # Relative paths of the OUTPUT will be intepreted relative to the build tree
# # directory corresponding to the current source directory
# add_custom_command(
#   OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/${PROTO_NAME}.pb.cc"
#          "${CMAKE_CURRENT_SOURCE_DIR}/${PROTO_NAME}.pb.h"
#   DEPENDS protoc "./${PROTO_NAME}.proto"
#   WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#   COMMAND ${CMAKE_BINARY_DIR}/output/protoc -I=. --cpp_out=. ${PROTO_NAME}.proto
#   COMMENT "Running C++ protocol buffer compiler on ${PROTO_NAME}.proto"
#   VERBATIM
# )

# # add_custom_target(generate_proto
# #   DEPENDS ${PROTO_SRCS} ${PROTO_HEADERS}
# #   COMMENT "generate proto target"
# #   VERBATIM
# # )

# add_executable(test_pb
#   main.cc
#   ${PROTO_SRCS}
#   ${PROTO_HEADERS}
# )

add_custom_command(
  OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/test.pb.cc"
         "${CMAKE_CURRENT_SOURCE_DIR}/test.pb.h"
  DEPENDS protoc "./test.proto"
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMAND ${CMAKE_BINARY_DIR}/output/protoc -I=. --cpp_out=. test.proto
  COMMENT "Running C++ protocol buffer compiler on test.proto"
  VERBATIM
)

add_executable(test_pb
  main.cc
  test.pb.cc
)

target_link_libraries(test_pb
  protobuf::libprotobuf
)

get_target_property(PROP test_pb INCLUDE_DIRECTORIES)
message("${PROP}")