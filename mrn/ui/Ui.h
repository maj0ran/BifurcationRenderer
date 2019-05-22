//
// Created by Marian Cichy
//

#pragma once

#include <vector>
#include "Widget.h"

namespace mrn {
    namespace ui {
        class Ui {
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
