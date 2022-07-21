find_package(protobuf REQUIRED)


# -------------------------------
find_package(Threads)
# Stupid, does not support multi-thread compiling
if(NOT TARGET muduo::base)
  add_library(muduo::base UNKNOWN IMPORTED)
  set_target_properties(muduo::base PROPERTIES
    IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
    IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/build/lib/libmuduo_base.a"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/3rdparty/muduo-src"
  )
endif()

if(NOT TARGET muduo::net)
  add_library(muduo::net UNKNOWN IMPORTED)
  set_target_properties(muduo::net PROPERTIES
    IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
    IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/build/lib/libmuduo_net.a"
    INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/3rdparty/muduo-src"
  )
endif()
# -------------------------------

add_custom_command(
  OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/rpcheader.pb.cc"
         "${CMAKE_CURRENT_SOURCE_DIR}/rpcheader.pb.h"
  DEPENDS protobuf::protoc "./rpcheader.proto"
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMAND ${CMAKE_BINARY_DIR}/output/protoc -I=. --cpp_out=. rpcheader.proto
  COMMENT "Running C++ protocol buffer compiler on rpcheader.proto"
  VERBATIM
)

add_library(mprpc
  mprpcapplication.cc
  mprpcprovider.cc
  mprpcconfig.cc
  mprpcchannel.cc
  rpcheader.pb.cc
)

target_include_directories(mprpc
  PUBLIC include
)

target_link_libraries(mprpc
  PRIVATE protobuf::libprotobuf
  PUBLIC muduo::base
  PUBLIC muduo::net
  PRIVATE Threads::Threads
)

add_library(mprpc::mprpc ALIAS mprpc)