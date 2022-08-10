# find_package(protobuf REQUIRED)

# # Relative paths of the OUTPUT will be intepreted relative to the build tree
# # directory corresponding to the current source directory
# add_custom_command(

# protobuf_generate(TARGET test_pb
#   PROTOS ${CMAKE_CURRENT_SOURCE_DIR}/test.proto    
# )
# include(FetchContent)
# set(FETCHCONTENT_BASE_DIR ${CMAKE_SOURCE_DIR}/3rdparty)
# set(FETCHCONTENT_QUIET off)
# # Protobuf
# FetchContent_Declare(
#   protobuf
#   GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
#   GIT_TAG        v3.21.2
#   # OVERRIDE_FIND_PACKAGE
#   FIND_PACKAGE_ARGS NAMES Protobuf
# )
# option(protobuf_BUILD_TESTS OFF)  # OR ADD DEF -Dprotobuf_USE_EXTERNAL_GTEST=ON
# FetchContent_MakeAvailable(protobuf)


add_custom_command(
  OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/test.pb.cc"
         "${CMAKE_CURRENT_SOURCE_DIR}/test.pb.h"
  DEPENDS protobuf::protoc "./test.proto"
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
