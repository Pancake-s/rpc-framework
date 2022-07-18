find_package(Protobuf)

add_library(mprpc
  mprpcapplication.cc
  mprpcprovider.cc
)

target_include_directories(mprpc
  PUBLIC include
)

add_library(mprpc::mprpc ALIAS mprpc)