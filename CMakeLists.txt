cmake_minimum_required(VERSION 3.6)

project(tests)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} BigInt.cpp BigIntTest.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE GTest::GTest)

