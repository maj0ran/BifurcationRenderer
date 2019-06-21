//
// Created by Marian Cichy
//

#include "Scene.h"
#include <ext.hpp>

namespace mrn {

    Scene::Scene() : //cam(glm::half_pi<float>(),
                     //    glm::half_pi<float>(),
                     //    1.0f, vec3(0.0f, 0.0f, 0.0f))
                     cam(vec3(0,0,0), vec3(-1,0,0))
                         {
        objects = std::vector<Model>();
    }

    Scene::~Scene() {

    }

    void Scene::render() {

        // First, we update the Camera-View & Projection
        cam.update();

        // Then we iterate through all objects to apply the shader and transform them into the world
        for(Model& o : objects) {
            o.shader->use();
            GLint proj_loc = glGetUniformLocation(o.shader->id, "projection");
            GLint view_loc = glGetUniformLocation(o.shader->id, "view");
            GLint model_loc = glGetUniformLocation(o.shader->id, "model");

            glUniformMatrix4fv(model_loc, 1, GL_FALSE, value_ptr(o.getTranslationMat()));
            glUniformMatrix4fv(view_loc, 1, GL_FALSE, value_ptr(cam.getViewMatrix()));
            glUniformMatrix4fv(proj_loc, 1, GL_FALSE, value_ptr(cam.projection));

            o.bind();
            if(o.vertex_data->use_indices)
                glDrawElements(GL_TRIANGLES, o.vertex_data->indices.size(), GL_UNSIGNED_INT, 0);
            else
                glDrawArrays(o.vertex_data->draw_type, 0, o.vertex_data->vertices.size());
        }
    }

    void Scene::addSceneNode(Model &model) {
        this->objects.push_back(model);
    }

    void Scene::setPolygonMode(uint16 mode) {
        assert(mode == GL_FILL || GL_LINE || GL_POINT);
        this->polygon_mode = mode;
    }
}
