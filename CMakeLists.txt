cmake_minimum_required(VERSION 3.22)
project(GameEngine C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# GLAD and GLFW
add_library(glad external/glad/src/gl.c)

include_directories(
        include
        external/glad/include
        external/glfw/include
)

include(FetchContent)

# Download GLFW automatically
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG        latest
)
FetchContent_MakeAvailable(glfw)

add_executable(GameEngine
        main.c
        src/core/window.c
        src/renderer/renderer.c
        # add other modules here
)

target_link_libraries(GameEngine glfw glad ${CMAKE_DL_LIBS})