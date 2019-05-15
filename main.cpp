#include <iostream>


#include <glad/glad.h>
#include <glfw3.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "mrn/engine/Window.h"
#include "mrn/engine/FontRenderer.h"
#include "mrn/engine/Vertex.h"
#include "mrn/engine/Line.h"
#include "mrn/engine/Model.h"
#include "mrn/engine/Scene.h"
#include "mrn/application/CoordSystem3D.h"
#include "mrn/engine/Primitives.h"
#include "mrn/MathSolver.h"

#include <gtc/matrix_transform.hpp>
#include <glm.hpp>
#include <ext.hpp>

void processInput(GLFWwindow *window, mrn::Scene* scene) {


}

int main() {
    MathSolver m = MathSolver();

    std::vector<std::array<float, 3>> result = m.solve();

    int row_length = 40;

    mrn::Mesh mesh = mrn::Mesh();
    for(int y = 0; y < 40; y++) {
        for(int x = 0; x < 40; x++) {
               mrn::Vertex v;
               v.pos = vec3(result[x + y * row_length][0], result[x + y * row_length][1], result[x + y * row_length][2]);
               v.rgb = vec3(1.0 - (result[x + y * row_length][1] / 8.0), result[x + y * row_length][1] / 8.0, 0.0);
               mesh.vertices.push_back(v);
        }
    }

    for(uint32 k = 0; k < result.size() - row_length - 1; k++) {
        if(((k + 1) % row_length) == 0)
            k++;
        uint32 i1 = k;
        uint32 i2 = k + 1;
        uint32 i3 = k + row_length;

        uint32 j1 = k + 1;
        uint32 j2 = k + row_length;
        uint32 j3 = (k + 1) + row_length;

        mesh.indices.push_back(i1);
        mesh.indices.push_back(i2);
        mesh.indices.push_back(i3);
        mesh.indices.push_back(j1);
        mesh.indices.push_back(j2);
        mesh.indices.push_back(j3);
    }




    mrn::Window* w = new mrn::Window(1200, 800);
    mrn::FontRenderer* fontRenderer = new mrn::FontRenderer();
    glViewport(0, 0, 1200, 800);
    glEnable(GL_DEPTH_TEST);
    glLineWidth(1);
    glPointSize(3);

    mrn::Shader s("shader/default_mvp.vert", "shader/default.frag");

    mrn::Model vis = mrn::Model();
    vis.vertex_data = &mesh;
    vis.shader = &s;
    mesh.initBuf();

    glm::mat4 projection = perspective(radians(45.0f), 1200.0f / 800.0f, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(vec3(0.0, 0.0, 3.0), vec3(0.0, 0.0, 2.0), vec3(0.0, 1.0, 0.0));

    // mat4 view = mat4(1.0);
    //  mat4 projection = mat4(1.0);
    mat4 trans = mat4(1.0);


    mrn::Model grid;
    mrn::Scene* scene = new mrn::Scene();

    scene->objects.push_back(vis);

    uint64 vertex_count = vis.vertex_data->vertices.size();

    mrn::CoordSystem3D coord_sys = mrn::CoordSystem3D();
    coord_sys.initBuf();
    grid.vertex_data = &coord_sys;
    grid.shader = &s;

    scene->objects.push_back(grid);

    std::string fps_str;
    int t = 0;
    int t_new = 0;
  //  fontRenderer->setFontSize(16);
    fontRenderer->setFont("fonts/arial.ttf");
    while(!w->shouldClose()) {
        w->clear();
        t = (int)glfwGetTime();
        if(t > t_new) {
            t_new = t;
            double fps = 1 / w->getDeltaTime();
            fps_str = std::to_string(fps);
        }
        fontRenderer->renderText("FPS: " + fps_str, 0, 0, vec3(1.0, 0, 0));
     //   fontRenderer->renderText("Vertex Count: " + std::to_string(vertex_count), 0, 0, vec3(1.0, 1.0, 0.0));
        scene->render();
        w->processInput(*scene);

        // glfw: poll events & swap buffers
        // --------------------------------
        w->swapBuffers();
        glfwPollEvents();
    }
    return 0;
}