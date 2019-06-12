//
// Created by mrn on 19/05/27.
//

#pragma once

#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

class Interface {
public:

    Interface(GLFWwindow* window);
    ~Interface();

    void startFrame();
};


