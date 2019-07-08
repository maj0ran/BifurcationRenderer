cmake_minimum_required(VERSION 3.13)
project(BifurcationRenderer)

set(CMAKE_CXX_STANDARD 14)
#SET(CMAKE_XXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
# GLFW
add_subdirectory(3rdparty/glfw-3.3)
include_directories(3rdparty/glfw-3.3/include/)

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

#dear-imgui
include_directories(3rdparty/imgui)

# Compilation and Linking
set(SOURCES main.cpp
        3rdparty/glad/src/glad.c
        3rdparty/imgui/imgui.cpp
        3rdparty/imgui/imgui_widgets.cpp
        3rdparty/imgui/imgui_draw.cpp
        3rdparty/imgui/imgui_impl_glfw.cpp
        3rdparty/imgui/imgui_impl_opengl3.cpp
        3rdparty/delaunay/delaunator.hpp
        3rdparty/Eigen/Dense
        mrn/engine/Window.cpp
        mrn/engine/FontRenderer.cpp
        mrn/engine/Shader.cpp
        mrn/engine/Model.cpp
        mrn/engine/Scene.cpp
        mrn/engine/cameras/FpsCamera.cpp
        mrn/application/CoordSystem3D.cpp
        mrn/application/CoordSystem3D.h
        mrn/engine/Line.cpp mrn/engine/Line.h
        mrn/engine/Mesh.cpp mrn/engine/Mesh.h
        mrn/engine/Renderer.cpp mrn/engine/Renderer.h
        mrn/engine/common.h
        mrn/engine/cameras/ArcballCamera.cpp
        mrn/engine/cameras/ArcballCamera.h
        mrn/engine/Primitives.cpp
        mrn/MathSolver.cpp mrn/MathSolver.h
        mrn/engine/cameras/Camera.cpp mrn/engine/cameras/Camera.h
        mrn/engine/Engine.cpp mrn/engine/Engine.h mrn/application/Trashcan/P.cpp mrn/application/Trashcan/P.h mrn/engine/eventbus/Event.cpp mrn/engine/eventbus/Event.h mrn/engine/eventbus/EventBus.cpp mrn/engine/eventbus/EventBus.h mrn/engine/eventbus/BusNode.cpp mrn/engine/eventbus/BusNode.h mrn/engine/eventbus/EventTypes.h mrn/application/Interface.cpp mrn/application/Interface.h mrn/application/Trashcan/Gauss.cpp mrn/application/Trashcan/Gauss.h mrn/engine/TriangleIndex.cpp mrn/engine/TriangleIndex.h mrn/application/Bifurcation/Bifurcation.cpp mrn/application/Bifurcation/Bifurcation.h mrn/application/Bifurcation/Vertex.cpp mrn/application/Bifurcation/Vertex.h mrn/application/Bifurcation/Mesher.cpp mrn/application/Bifurcation/Mesher.h mrn/application/Bifurcation/Edge.cpp mrn/application/Bifurcation/Edge.h mrn/application/Bifurcation/Front.cpp mrn/application/Bifurcation/Front.h mrn/application/Bifurcation/Triangle.cpp mrn/application/Bifurcation/Triangle.h mrn/application/Bifurcation/Circumsphere.cpp mrn/application/Bifurcation/Circumsphere.h mrn/Debug.cpp mrn/Debug.h mrn/application/Bifurcation/Mesh.cpp mrn/application/Bifurcation/Mesh.h mrn/application/FileIO.cpp mrn/application/FileIO.h)


add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} glfw freetype)

# Forcing CMake to copy non-code files in the build directory
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/shader $<TARGET_FILE_DIR:${PROJECT_NAME}>/shader)
# add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/textures $<TARGET_FILE_DIR:${PROJECT_NAME}>/textures)
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/fonts $<TARGET_FILE_DIR:${PROJECT_NAME}>/fonts)