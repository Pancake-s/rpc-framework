find_package(protobuf REQUIRED)

add_library(mprpc
  mprpcapplication.cc
  mprpcprovider.cc
)

target_include_directories(mprpc
  PUBLIC include
)

target_link_libraries(mprpc
  PRIVATE protobuf::libprotobuf
)

add_library(mprpc::mprpc ALIAS mprpc)