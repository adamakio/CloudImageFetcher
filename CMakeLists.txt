cmake_minimum_required(VERSION 3.14)
project(CloudImageFetcher)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(CloudImageFetcher "${PROJECT_SOURCE_DIR}/src/main.cpp")