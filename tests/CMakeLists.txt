include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

add_executable(tests
    ${CMAKE_SOURCE_DIR}/src/core/Grid.cpp
    test_grid.cpp
)

target_link_libraries(tests
    gtest_main
)

target_include_directories(tests PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
)

include(GoogleTest)
gtest_discover_tests(tests)