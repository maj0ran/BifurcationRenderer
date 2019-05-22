//
// Created by Marian Cichy
//

#pragma once

#include <string>
#include "../engine/Renderable.h"
#include "../engine/Shader.h"
#include "WidgetElement.h"

namespace mrn {
    namespace ui {

        class Widget {
        public:
            Widget(std::string title, float x, float y, float width, float height);
            ~Widget();

            std::string title;

            float x;
            float y;
            float width;
            float height;

            Renderable* vertex_data = new Renderable();
            Shader* shader;

            void addElement(WidgetElement* e);
            void render();
        private:
            std::vector<WidgetElement*> elements;
        };
    }
}

