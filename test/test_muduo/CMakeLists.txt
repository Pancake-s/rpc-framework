find_package(Threads)

# -- Stupid Muduo
# if(NOT TARGET muduo::muduo)
#   add_library(muduo::muduo UNKNOWN IMPORTED)
#   set_target_properties(muduo::muduo PROPERTIES
#     IMPORTED_LINK_INTERFACE_LANGUAGES "CXX"
#     IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/build/lib/libmuduo_base.a"
#     IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/build/lib/libmuduo_net.a"
#     INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/3rdparty/muduo-src"
#   )
# endif()

add_executable(test_muduo main.cc)

target_include_directories(test_muduo
  PRIVATE "${CMAKE_SOURCE_DIR}/3rdparty/muduo-src"
)

target_link_directories(test_muduo
  PRIVATE "${CMAKE_SOURCE_DIR}/build/lib"
)

target_compile_features(test_muduo PRIVATE cxx_std_11)

target_link_libraries(test_muduo
  # PUBLIC muduo::muduo
  PRIVATE libmuduo_base.a
  PRIVATE libmuduo_net.a
  PRIVATE Threads::Threads
)
