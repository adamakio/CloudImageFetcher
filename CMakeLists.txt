cmake_minimum_required(VERSION 3.14)
project(CloudImageFetcher)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add vcpkg toolchain
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

# Set platform-dependent CMAKE_PREFIX_PATH
if (WIN32)
    set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/vcpkg/installed/x64-windows")
elseif (UNIX AND NOT APPLE)
    set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/vcpkg/installed/x64-linux")
elseif (APPLE)
    set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/vcpkg/installed/x64-osx")
endif()

include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(CloudImageFetcher "src/main.cpp" "src/ImageFetcher.cpp")

# Link libraries
find_package(nlohmann_json REQUIRED)
find_package(CURL REQUIRED)
target_link_libraries(CloudImageFetcher PRIVATE nlohmann_json::nlohmann_json CURL::libcurl)
if (UNIX)
    find_package(ZLIB REQUIRED)
    find_package(OpenSSL REQUIRED)
    target_link_libraries(CloudImageFetcher PRIVATE ZLIB::ZLIB OpenSSL::SSL)
endif()

