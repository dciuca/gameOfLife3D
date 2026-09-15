cmake_minimum_required(VERSION 3.15)
project(gameOfLife3D)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# === DEPENDENCIES ===
include(FetchContent)
set(RAYLIB_VERSION 6.0)
FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    FIND_PACKAGE_ARGS ${RAYLIB_VERSION}
)
set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(raylib)


# === CORE LIBRARY (senza Raylib) ===
add_library(gol_core STATIC
    src/core/Grid.cpp
    src/core/PatternLibrary.cpp
    # src/core/GameLoop.cpp
)
target_include_directories(gol_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


# === PLATFORM LIBRARY (con Raylib) ===
add_library(gol_platform STATIC
    src/platform/RaylibInputHandler.cpp
    src/platform/RaylibRenderer.cpp
)
target_link_libraries(gol_platform PUBLIC gol_core raylib)


# === EXECUTABLE ===
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE gol_platform)

# === RESOURCES ===
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)

# === TESTS ===
option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()