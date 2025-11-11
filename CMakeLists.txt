cmake_minimum_required(VERSION 3.15)
project(password_manager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# tell CMake where brew installs libsodium
set(SODIUM_ROOT "/opt/homebrew/opt/libsodium")

# include + lib paths manually if find_package fails
include_directories(${SODIUM_ROOT}/include)
link_directories(${SODIUM_ROOT}/lib)

# add your source files
add_executable(password_manager
    src/main.cpp
    src/crypto.cpp
    src/storage.cpp
    # add more .cpps here
)

# try to find libsodium via pkg-config or fallback
find_package(PkgConfig)
if (PkgConfig_FOUND)
    pkg_check_modules(SODIUM libsodium)
    if (SODIUM_FOUND)
        target_include_directories(password_manager PRIVATE ${SODIUM_INCLUDE_DIRS})
        target_link_directories(password_manager PRIVATE ${SODIUM_LIBRARY_DIRS})
    endif()
endif()

# link libsodium
target_link_libraries(password_manager PRIVATE sodium)
