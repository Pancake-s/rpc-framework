include(FetchContent)
set(FETCHCONTENT_BASE_DIR ${CMAKE_SOURCE_DIR}/3rdparty)
set(FETCHCONTENT_QUIET off)
# Protobuf
FetchContent_Declare(
  protobuf
  GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
  GIT_TAG        v3.21.2
  # OVERRIDE_FIND_PACKAGE
  FIND_PACKAGE_ARGS NAMES Protobuf
)
option(protobuf_BUILD_TESTS OFF)  # OR ADD DEF -Dprotobuf_USE_EXTERNAL_GTEST=ON
FetchContent_MakeAvailable(protobuf)

# Boost
# FetchContent_Declare(
#   boost
#   GIT_REPOSITORY https://github.com/boostorg/boost.git
#   GIT_TAG        boost-1.79.0
#   # OVERRIDE_FIND_PACKAGE
#   FIND_PACKAGE_ARGS NAMES Boost
# )
# FetchContent_MakeAvailable(boost)

# Muduo
FetchContent_Declare(
  muduo
  GIT_REPOSITORY https://github.com/chenshuo/muduo.git
  GIT_TAG        v2.0.2
  OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(muduo)
