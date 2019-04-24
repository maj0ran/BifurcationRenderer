//
// Created by Marian Cichy
//
#include <iostream>
#include "Window.h"

mrn::Window::Window(int width, int height) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    this->window = glfwCreateWindow(width, height, "Bifurcation Renderer", nullptr, nullptr);

    if(window == nullptr) {
        std::cout << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
    }
    glfwGetWindowSize(this->window, &this->width, &this->height);
    glfwSetWindowUserPointer(this->window, this);
    glfwMakeContextCurrent(this->window);


    glfwSetFramebufferSizeCallback(window, frambuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);


    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
    }


}

mrn::Window::~Window() = default;

double mrn::Window::getDeltaTime() {
    return deltaTime;
}


void mrn::Window::processInput(Scene &scene) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    if(glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }

    // camera control

    if(glfwGetKey(window, GLFW_KEY_W)) {
        scene.cam.theta -= glm::radians(0.1f);
        if(scene.cam.theta < 0.01) {
            scene.cam.theta = 0.01;
        }
    }

    if(glfwGetKey(window, GLFW_KEY_S)) {
        scene.cam.theta += glm::radians(0.1f);

        if(scene.cam.theta > glm::pi<float>() - 0.01f) {
            scene.cam.theta = glm::pi<float>() - 0.01f;
        }
    }

    if(glfwGetKey(window, GLFW_KEY_A)) {
        scene.cam.phi += glm::radians(0.1f);
    }

    if(glfwGetKey(window, GLFW_KEY_D)) {
        scene.cam.phi -= glm::radians(0.1f);
    }

    if(glfwGetKey(window, GLFW_KEY_Z)) {
        scene.cam.distance -= 0.02;
    }

    if(glfwGetKey(window, GLFW_KEY_X)) {
        scene.cam.distance += 0.02;
    }
}

void mrn::Window::clear() {
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    currentFrameTime = glfwGetTime();
    deltaTime = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;
}

void mrn::Window::eventLoop() {

}

int mrn::Window::getWidth() const {
    return width;
}

int mrn::Window::getHeight() const {
    return height;
}

void mrn::Window::swapBuffers() const {
    glfwSwapBuffers(this->window);
}

int mrn::Window::shouldClose() const {
    return glfwWindowShouldClose(this->window);
}

void mrn::Window::frambuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));
    w->width = width;
    w->height = height;
}

void mrn::Window::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    printf("Pressed: %d\n", key);
}

void mrn::Window::setPolygonMode(short mode) {
    assert(mode == GL_FILL || GL_LINE || GL_POINT);
    this->polygon_mode = mode;
}


