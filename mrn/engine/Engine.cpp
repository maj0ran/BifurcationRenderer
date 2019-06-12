//
// Created by Marian Cichy
//

#include "Engine.h"

mrn::Engine::Engine() {

    eventbus = new EventBus();
}

mrn::Engine::~Engine() {

}

mrn::Window *mrn::Engine::getWindow() {
    return this->window;
}

void mrn::Engine::createWindow(uint32_t width, uint32_t height) {
    window = new Window(width, height);
    fontRenderer = new FontRenderer();
    window->attach(this->eventbus);
    fontRenderer->attach(this->eventbus);

}

void mrn::Engine::createScene() {
    this->activeScene = new Scene();
    activeScene->cam.attach(this->eventbus);
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

mrn::FontRenderer *mrn::Engine::getFontRenderer() {
    return this->fontRenderer;
}

mrn::EventBus *mrn::Engine::getEventBus() {
    return this->eventbus;
}

