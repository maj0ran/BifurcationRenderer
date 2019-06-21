//
// Created by Marian Cichy
//

#pragma once

#include "cameras/FpsCamera.h"
#include "Model.h"
#include "cameras/ArcballCamera.h"

namespace mrn {

    class Scene {
    public:
        Scene();
        ~Scene();
        void addSceneNode(mrn::Model &model);
        mrn::FpsCamera cam;


        void render();
        void setPolygonMode(uint16 mode);

    private:
        std::vector<mrn::Model> objects;
        uint16 polygon_mode;
    };
}