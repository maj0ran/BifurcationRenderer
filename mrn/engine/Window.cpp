//
// Created by Marian Cichy
//
#include <iostream>
#include "Window.h"

mrn::Window::Window(uint32_t width, uint32_t height) :
width(width),
height(height),
currentFrameTime(0),
lastFrameTime(0),
deltaTime(0)
{
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
    glfwSetWindowUserPointer(this->window, this); // used for accessing this class from glfw callbacks
    glfwMakeContextCurrent(this->window);


    glfwSetFramebufferSizeCallback(window, frambuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);


    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
    }

    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
    glLineWidth(1);
    glPointSize(3);



}

mrn::Window::~Window() = default;

double mrn::Window::getDeltaTime() {
    return deltaTime;
}


void mrn::Window::processInput(Scene* scene) {

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
    float camSpeed = 60.0;
    float zoomSpeed = 15.0;
    if(glfwGetKey(window, GLFW_KEY_W)) {
        scene->cam.theta -= glm::radians(camSpeed * deltaTime);
        if(scene->cam.theta < 0.01) {
            scene->cam.theta = 0.01;
        }
    }

    if(glfwGetKey(window, GLFW_KEY_S)) {
        scene->cam.theta += glm::radians(camSpeed * deltaTime);

        if(scene->cam.theta > glm::pi<float>() - 0.01f) {
            scene->cam.theta = glm::pi<float>() - 0.01f;
        }
    }

    if(glfwGetKey(window, GLFW_KEY_A)) {
        scene->cam.phi += glm::radians(camSpeed * deltaTime);
    }

    if(glfwGetKey(window, GLFW_KEY_D)) {
        scene->cam.phi -= glm::radians(camSpeed * deltaTime);
    }

    if(glfwGetKey(window, GLFW_KEY_Z)) {
        scene->cam.distance -= zoomSpeed * deltaTime;
    }

    if(glfwGetKey(window, GLFW_KEY_X)) {
        scene->cam.distance += zoomSpeed * deltaTime;
    }
}


void mrn::Window::eventLoop() {

}

int mrn::Window::getWidth() const {
    return width;
}

int mrn::Window::getHeight() const {
    return height;
}



int mrn::Window::shouldClose() const {
    return glfwWindowShouldClose(this->window);
}

void mrn::Window::frambuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));
    w->width = width;
    w->height = height;

  //  w->send(new Event());

    printf("Window Size: [%d | %d]\n", width, height);
} //  this->conn.sendEvent();//

void mrn::Window::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));
    w->send(Event());
    printf("Pressed: %d\n", key);
}

void mrn::Window::setPolygonMode(short mode) {
    assert(mode == GL_FILL || GL_LINE || GL_POINT);
    this->polygon_mode = mode;
}

void mrn::Window::nextFrame() {
    glfwSwapBuffers(this->window);

    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    currentFrameTime = glfwGetTime();
    deltaTime = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;
   // printf("%f\n", deltaTime);
}

void mrn::Window::onNotify(mrn::Event &e) { }


