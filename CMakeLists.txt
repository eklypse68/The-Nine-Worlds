cmake_minimum_required(VERSION 3.20)

project(TheNineWorlds
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --------------------------------------------------
# raylib
# --------------------------------------------------

set(RAYLIB_DIR "${CMAKE_SOURCE_DIR}/src/deps/raylib")

if(NOT EXISTS "${RAYLIB_DIR}/CMakeLists.txt")
    message(STATUS "raylib not found. Cloning raylib...")

    execute_process(
        COMMAND git clone --depth 1 --branch 5.5
                https://github.com/raysan5/raylib.git
                "${RAYLIB_DIR}"
        RESULT_VARIABLE RAYLIB_CLONE_RESULT
    )

    if(NOT RAYLIB_CLONE_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to clone raylib.")
    endif()
else()
    message(STATUS "Found local raylib: ${RAYLIB_DIR}")
endif()

add_subdirectory("${RAYLIB_DIR}" "${CMAKE_BINARY_DIR}/raylib")

# --------------------------------------------------
# Source files
# --------------------------------------------------

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

# --------------------------------------------------
# Game
# --------------------------------------------------

add_executable(TheNineWorlds ${SOURCES})


# Hide the console window in Release builds.
set_target_properties(TheNineWorlds PROPERTIES
    WIN32_EXECUTABLE FALSE
)


target_include_directories(TheNineWorlds PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
)

target_link_libraries(TheNineWorlds PRIVATE
    raylib
)