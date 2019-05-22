//
// Created by Marian Cichy
//

#include "Engine.h"

mrn::Engine::Engine() {

}

mrn::Engine::~Engine() {

}

mrn::Window *mrn::Engine::getWindow() {
    return this->window;
}

void mrn::Engine::createWindow(uint32_t width, uint32_t height) {
    window = new Window(width, height);
}

void mrn::Engine::createScene() {
    this->activeScene = new Scene();
}

mrn::Scene *mrn::Engine::getScene() {
    return activeScene;
}

void mrn::Engine::renderScene() {
    activeScene->render();

}

void mrn::Engine::processInput() {
    window->processInput(activeScene);
}
