cmake_minimum_required(VERSION 3.13)
project(BifurcationRenderer)

set(CMAKE_CXX_STANDARD 17)

# GLFW
find_library(GLFW NAMES libglfw3 PATHS 3rdparty/glfw/lib)
include_directories(3rdparty/glfw/include/GLFW)

# GLAD
include_directories(3rdparty/glad/include)

# GLM
include_directories(3rdparty/glm/include)

# FREETYPE
find_library(FT NAMES libfreetype PATHS 3rdparty/freetype/lib)
include_directories(3rdparty/freetype/include)

# Compilation and Linking
set(SOURCES main.cpp
        3rdparty/glad/src/glad.c
        mrn/engine/Window.cpp
        mrn/engine/FontRenderer.cpp
        mrn/engine/Shader.cpp
        mrn/engine/Mesh.cpp
        mrn/engine/Model.cpp
        mrn/engine/Scene.cpp
        mrn/engine/cameras/FpsCamera.cpp
        mrn/application/CoordSystem3D.cpp
        mrn/application/CoordSystem3D.h
        mrn/engine/Line.cpp mrn/engine/Line.h
        mrn/engine/Renderable.cpp mrn/engine/Renderable.h
        mrn/engine/Renderer.cpp mrn/engine/Renderer.h
        mrn/engine/common.h
        mrn/engine/cameras/ArcballCamera.cpp
        mrn/engine/cameras/ArcballCamera.h
        mrn/engine/Primitives.cpp
        mrn/MathSolver.cpp mrn/MathSolver.h mrn/engine/cameras/Camera.cpp mrn/engine/cameras/Camera.h)


add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${GLFW} ${FT})

# Forcing CMake to copy non-code files in the build directory
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shader $<TARGET_FILE_DIR:${PROJECT_NAME}>/shader)
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/textures $<TARGET_FILE_DIR:${PROJECT_NAME}>/textures)
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/textures $<TARGET_FILE_DIR:${PROJECT_NAME}>/fonts)