//
// Created by Marian Cichy
//

#pragma once

namespace mrn {
    namespace ui {
        class WidgetElement {
        public:
            WidgetElement(int x, int y, int width, int height);
            virtual ~WidgetElement();

            int x;
            int y;
            int width;
            int height;

        };
    }
}

