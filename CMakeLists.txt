cmake_minimum_required(VERSION 3.21)
project(cterm
    VERSION 1.0.2
    LANGUAGES CXX
)

cmake_policy(SET CMP0135 NEW)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    "${CMAKE_SOURCE_DIR}/output/${CMAKE_BUILD_TYPE}"
)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
find_package(QTermWidget6 REQUIRED)

include(FetchContent)

message(STATUS "Fetching nlohmann::json...")
set(JSON_BuildTests OFF CACHE INTERNAL "")
FetchContent_Declare(json
    URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
)
FetchContent_MakeAvailable(json)

message(STATUS "Fetching CLI11...")
FetchContent_Declare(cli11
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG v2.7.2
)
FetchContent_MakeAvailable(cli11)

qt_standard_project_setup()
qt_add_executable(${PROJECT_NAME}
    src/config.cpp
    src/keymap.cpp
    src/cterm.cpp
    src/main.cpp
)

target_compile_definitions(cterm PRIVATE
    PROJECT_VERSION="${PROJECT_VERSION}"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Widgets
    qtermwidget6
    nlohmann_json::nlohmann_json
    CLI11::CLI11
)
