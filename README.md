# Ubuntu Cloud Image Fetcher

## Description

Ubuntu Cloud Image Fetcher is a command-line tool written in C++ that fetches the latest Ubuntu Cloud image information in Simplestreams format. It provides methods to:
- Return a list of all currently supported Ubuntu releases.
- Return the current Ubuntu LTS version.
- Return the SHA256 checksum of the `disk1.img` item of a given Ubuntu release.

The data is fetched from the URL: [https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json](https://cloud-images.ubuntu.com/releases/streams/v1/com.ubuntu.cloud:released:download.json).

## Prerequisites

- CMake 3.14 or higher
- C++17 compatible compiler (e.g., g++, clang++)
- libcurl (with openssl and zlib)
- nlohmann-json

## Build Instructions

1. Clone the repository:
    ```
    git clone --recurse-submodules https://github.com/adamakio/CloudImageFetcher.git
    cd CloudImageFetcher
    ```

2. Download dependencies using vcpkg:
    ```
    ./vcpkg/bootstrap-vcpkg.bat (Windows)
    ./vcpkg/bootstrap-vcpkg.sh (Linux)
    ./vcpkg/vcpkg integrate install
    ./vcpkg/vcpkg install nlohmann-json curl
    ./vcpkg/vcpkg install openssl zlib (Linux)
    ```
    
2. Create a build directory:
    ```
    mkdir build
    cd build
    ```

3. Run CMake to configure the project and generate the Makefile:
    ```
    cmake ..
    ```

4. Build the project:

- For Windows:
	```
	cmake --build . --config Release
    cd Release
    ./CloudImageFetcher
	```
- For Linux:
    ```
    make
    ./CloudImageFetcher
	```     

## Usage
The executable `CloudImageFetcher` provides several options:

- `--releases`: List supported releases.
- `--versions`: List supported versions under releases (requires `--releases`).
- `--current`: Find the current LTS version.
- `--sha256 <pubname>`: Find the SHA256 checksum of a release by pubname.
- `--help`: Display the help message.

### Examples

1. List all supported releases:
    ```
    ./CloudImageFetcher --releases
    ```

2. List all supported releases with their versions:
    ```
    ./CloudImageFetcher --releases --versions
    ```

3. Find the current LTS version:
    ```
    ./CloudImageFetcher --current
    ```

4. Find the SHA256 checksum of a release by pubname:
    ```
    ./CloudImageFetcher --sha256 ubuntu-lucid-10.04-amd64-server-20150427
    ```

## License
This project is licensed under the MIT License 
