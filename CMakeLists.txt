cmake_minimum_required(VERSION 3.20)

project(TheNineWorlds
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(DEPS_DIR "${CMAKE_SOURCE_DIR}/src/deps")

function(clone_dependency NAME URL PATH)
    if(NOT EXISTS "${PATH}")
        message(STATUS "${NAME} not found. Cloning...")
        execute_process(
            COMMAND git clone "${URL}" "${PATH}"
            RESULT_VARIABLE CLONE_RESULT
        )

        if(NOT CLONE_RESULT EQUAL 0)
            message(FATAL_ERROR "Failed to clone ${NAME}.")
        endif()
    endif()
endfunction()

set(SDL_DIR "${DEPS_DIR}/SDL")
clone_dependency(
    "SDL3"
    "https://github.com/libsdl-org/SDL.git"
    "${SDL_DIR}"
)

set(SDL_TESTS OFF CACHE BOOL "" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(
    "${SDL_DIR}"
    "${CMAKE_BINARY_DIR}/SDL"
)

set(GLM_DIR "${DEPS_DIR}/glm")
clone_dependency(
    "GLM"
    "https://github.com/g-truc/glm.git"
    "${GLM_DIR}"
)

add_library(glm INTERFACE)

target_include_directories(glm INTERFACE
    "${GLM_DIR}"
)

set(JOLT_DIR "${DEPS_DIR}/JoltPhysics")
clone_dependency(
    "Jolt Physics"
    "https://github.com/jrouwe/JoltPhysics.git"
    "${JOLT_DIR}"
)

set(DOUBLE_PRECISION OFF CACHE BOOL "" FORCE)
set(GENERATE_DEBUG_SYMBOLS ON CACHE BOOL "" FORCE)
set(OVERRIDE_CXX_FLAGS OFF CACHE BOOL "" FORCE)
set(INTERPROCEDURAL_OPTIMIZATION OFF CACHE BOOL "" FORCE)

add_subdirectory(
    "${JOLT_DIR}/Build"
    "${CMAKE_BINARY_DIR}/Jolt"
)

set(BGFX_CMAKE_DIR "${DEPS_DIR}/bgfx.cmake")
set(BGFX_DIR "${DEPS_DIR}/bgfx")
set(BX_DIR "${DEPS_DIR}/bx")
set(BIMG_DIR "${DEPS_DIR}/bimg")

clone_dependency(
    "bgfx"
    "https://github.com/bkaradzic/bgfx.git"
    "${BGFX_DIR}"
)

clone_dependency(
    "bx"
    "https://github.com/bkaradzic/bx.git"
    "${BX_DIR}"
)

clone_dependency(
    "bimg"
    "https://github.com/bkaradzic/bimg.git"
    "${BIMG_DIR}"
)

clone_dependency(
    "bgfx.cmake"
    "https://github.com/bkaradzic/bgfx.cmake.git"
    "${BGFX_CMAKE_DIR}"
)

set(BGFX_DIR "${BGFX_DIR}" CACHE PATH "" FORCE)
set(BX_DIR "${BX_DIR}" CACHE PATH "" FORCE)
set(BIMG_DIR "${BIMG_DIR}" CACHE PATH "" FORCE)

set(BGFX_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BGFX_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(BGFX_BUILD_TOOLS OFF CACHE BOOL "" FORCE)
set(BGFX_LIBRARY_TYPE STATIC CACHE STRING "" FORCE)

add_subdirectory(
    "${BGFX_CMAKE_DIR}"
    "${CMAKE_BINARY_DIR}/bgfx"
)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

list(FILTER SOURCES EXCLUDE REGEX
    "${DEPS_DIR}/.*"
)

add_executable(TheNineWorlds
    ${SOURCES}
)

set_target_properties(TheNineWorlds PROPERTIES
    WIN32_EXECUTABLE FALSE
)

target_include_directories(TheNineWorlds PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
)

target_link_libraries(TheNineWorlds PRIVATE
    SDL3::SDL3
    glm
    Jolt
    bgfx
)

if(WIN32)
    add_custom_command(TARGET TheNineWorlds POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:SDL3-shared>"
            "$<TARGET_FILE_DIR:TheNineWorlds>"
    )
endif()