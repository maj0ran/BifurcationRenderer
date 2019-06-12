//
// Created by Marian Cichy
//
#include <iostream>
#include "Window.h"
#include "common.h"
#include <GLFW/glfw3.h>

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

    gladLoadGL();
 //   if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
 //       std::cout << "Failed to initialize GLAD" << std::endl;
 //       glfwTerminate();
 //   }

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

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        Event e = Event(KEY_W);
        e.addData(&deltaTime);
        send(e);
    }

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        Event e = Event(KEY_S);
        e.addData(&deltaTime);
        send(e);
    }

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        Event e = Event(KEY_A);
        e.addData(&deltaTime);
        send(e);
    }

    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        Event e = Event(KEY_D);
        e.addData(&deltaTime);
        send(e);
    }

    if(glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        Event e = Event(KEY_X);
        e.addData(&deltaTime);
        send(e);
    }

    if(glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        Event e = Event(KEY_Z);
        e.addData(&deltaTime);
        send(e);
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
    Window *w = static_cast<Window *>(glfwGetWindowUserPointer(window));
    glViewport(0, 0, width, height);
    w->width = width;
    w->height = height;
    ScreenSize size = { .width = width, .height = height};

    Event e = Event(WINDOW_RESIZE);
    e.addData(&size);
    w->send(e);

}

void mrn::Window::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    static int lastAction = 0;
    Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));
    Event e = Event(KEY_PRESSED);
    KeyEvent keyPress = { .key = key, .scancode = scancode, .action = action, .mods = mods };
    e.addData(&keyPress);
    w->send(e);
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
}

void mrn::Window::onNotify(mrn::Event &e) { }

GLFWwindow *mrn::Window::getGlfwWindowPtr() {
    return window;
}


