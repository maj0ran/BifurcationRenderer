//
// Created by Marian Cichy
//

#pragma once

#include <string>
#include "WidgetElement.h"

namespace mrn {
    namespace ui{
        class Label : public WidgetElement {
        public:
            Label(int x, int y, int width, int height);
            ~Label() override;

            std::string text = "";

            };
    }
}

