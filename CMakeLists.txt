cmake_minimum_required(VERSION 3.20)
project(Render3D)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(main src/main.cpp)
target_include_directories(main PRIVATE src)

add_executable(tests tests/src/main.cpp tests/src/math_test.cpp)
target_include_directories(tests PRIVATE src external/doctest)

enable_testing()
add_test(NAME tests COMMAND tests)
