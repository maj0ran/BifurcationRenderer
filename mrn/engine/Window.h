//
// Created by Marian Cichy
//

#pragma once

#include <glad/glad.h>
#include <glfw3.h>
#include "Scene.h"

namespace mrn {

    class Window {
    private:
        GLFWwindow* window;

        int width;
        int height;

        double currentFrameTime, lastFrameTime, deltaTime;

        static void frambuffer_size_callback(GLFWwindow* window, int width, int height);
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

        short polygon_mode = GL_FILL;

    public:
        Window(uint32_t width, uint32_t height);
        ~Window();

        void setPolygonMode(short mode);
        double getDeltaTime();
        void processInput(Scene *scene);



        void eventLoop();


        int getWidth() const;
        int getHeight() const;

        int shouldClose() const;

        void nextFrame();



 //       Scene* activeScene;
 //       void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    };

}


