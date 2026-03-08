cmake_minimum_required(VERSION 3.10)
project(Work_with_files)
file(GLOB SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})