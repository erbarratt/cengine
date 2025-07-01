cmake_minimum_required(VERSION 3.22)
project(GameEngine CXX)

set(CMAKE_CXX_STANDARD 17)

#define where to put the built exe after build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#literally add directories to look for headers when using <> in includes
include_directories(${CMAKE_SOURCE_DIR}/external/GLFW/include)
include_directories(${CMAKE_SOURCE_DIR}/external/GLEW/include)
include_directories(${CMAKE_SOURCE_DIR}/external/GLM)

#where to look for the library files that we link below...
link_directories(${CMAKE_SOURCE_DIR}/external/GLFW/lib-mingw-w64)
link_directories(${CMAKE_SOURCE_DIR}/external/GLEW/lib/Release/x64)

add_executable(GameEngine
        src/main.cpp
        src/render/Shader.cpp
        src/render/GLDebug.h
        src/render/VertexBufferLayout.cpp
        external/stb_image.cpp
        src/render/Texture.cpp
        src/core/Window.cpp
        src/systems/CameraSystem.cpp
        src/systems/InputSystem.cpp
        src/systems/RenderableSystem.cpp
        src/systems/RenderSystem.cpp
        src/core/Scene.cpp
        # add other modules here
)

target_link_libraries(GameEngine glfw3 glew32s opengl32)

add_compile_definitions(GLEW_STATIC)