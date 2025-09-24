cmake_minimum_required(VERSION 3.12)

project(advanced_cpp LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)
enable_testing()

include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.1
)

FetchContent_MakeAvailable(Catch2)  

set(SOURCES
    test.cpp
    vector.hpp
    vector.inl
)

add_executable(advanced-cpp ${SOURCES})

target_include_directories(advanced-cpp PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(advanced-cpp PRIVATE Catch2::Catch2WithMain)

include(Catch)
catch_discover_tests(advanced-cpp)
