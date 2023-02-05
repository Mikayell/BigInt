cmake_minimum_required(VERSION 3.6)

project(tests)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} BigIntTest.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE GTest::GTest)

