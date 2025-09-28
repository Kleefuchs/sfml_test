cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME "boykissies")
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

project(${PROJECT_NAME})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build/bin)

file(GLOB PROJECT_SRC CONFIGURE_DEPENDS "src/*.cpp")
message(PROJECT_SRC="${PROJECT_SRC}")

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

include_directories(
    headers
    /usr/local/include
)
add_executable(${PROJECT_NAME} ${PROJECT_SRC})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics)
