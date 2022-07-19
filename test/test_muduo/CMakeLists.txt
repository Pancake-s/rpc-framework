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

add_executable(test_muduo main.cc)

target_compile_features(test_muduo PRIVATE cxx_std_11)

target_link_libraries(test_muduo
  PRIVATE muduo::base
  PRIVATE muduo::net
  PRIVATE Threads::Threads
)
