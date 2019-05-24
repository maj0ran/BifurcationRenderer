//
// Created by Marian Cichy
//

#pragma once

#include "Window.h"
#include "eventbus/EventBus.h"
#include "FontRenderer.h"

namespace mrn {
    class Engine {
    public:
        Engine();
        ~Engine();

        void createWindow(uint32_t width, uint32_t height);
        void createScene();
        void renderScene();
        void processInput();

        mrn::Window* getWindow();
        mrn::Scene* getScene();
        mrn::FontRenderer* getFontRenderer();
        mrn::EventBus* getEventBus();

        bool createShader(const char* vertexPath, const char* fragmentPath);




    private:
        mrn::Window *window;
        mrn::EventBus *eventbus;
        mrn::Scene *activeScene;
        mrn::FontRenderer *fontRenderer;

    };


}