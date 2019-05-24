//
// Created by Marian Cichy
//

#pragma once

#include <vector>
#include "Widget.h"
#include "../engine/eventbus/BusNode.h"

namespace mrn {
    namespace ui {

        class Ui : public BusNode {
        public:
            Ui();
            ~Ui();

            void addWidget(Widget* w);

            void render();
        private:
            std::vector<Widget*> widgets;

        };
    }
}
