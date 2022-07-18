include(FetchContent)
set(FETCHCONTENT_BASE_DIR ${CMAKE_SOURCE_DIR}/3rdparty)
FetchContent_Declare(
  protobuf
  GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
  GIT_TAG        v3.21.2
  OVERRIDE_FIND_PACKAGE
)
option(protobuf_BUILD_TESTS OFF)  # OR ADD DEF -Dprotobuf_USE_EXTERNAL_GTEST=ON
FetchContent_MakeAvailable(protobuf)