cmake_minimum_required(VERSION 3.13)
project(BifurcationRenderer)

set(CMAKE_CXX_STANDARD 17)




# GLFW
add_subdirectory(3rdparty/glfw-3.3)
include_directories(3rdparty/glfw-3.3/include/GLFW)

# GLM
# GLM is header-only so no compiling needed
include_directories(3rdparty/glm/glm)

# GLAD
include_directories(3rdparty/glad/include)

#stb_image
include_directories(3rdparty/stb)

#Freetype
add_subdirectory(3rdparty/freetype-2.10.0)
include_directories(3rdparty/freetype-2.10.0/include)

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
target_link_libraries(${PROJECT_NAME} glfw freetype)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shader $<TARGET_FILE_DIR:${PROJECT_NAME}>/shader)
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/fonts $<TARGET_FILE_DIR:${PROJECT_NAME}>/fonts)
