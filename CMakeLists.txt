cmake_minimum_required(VERSION 3.20)
project(Render3D)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(render3d_lib src/canvas.cpp)
target_include_directories(render3d_lib PUBLIC src)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE render3d_lib)

add_executable(tests tests/src/main.cpp tests/src/math_test.cpp tests/src/colors_test.cpp tests/src/canvas_test.cpp)
target_link_libraries(tests PRIVATE render3d_lib)
target_include_directories(tests PRIVATE external/doctest)

enable_testing()
add_test(NAME tests COMMAND tests)
