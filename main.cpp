#include <iostream>


#include <glad/glad.h>
#include <glfw3.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "mrn/engine/Engine.h"

#include "mrn/engine/Window.h"
#include "mrn/engine/FontRenderer.h"
#include "mrn/engine/Vertex.h"
#include "mrn/engine/Line.h"
#include "mrn/engine/Model.h"
#include "mrn/engine/Scene.h"
#include "mrn/application/CoordSystem3D.h"
#include "mrn/engine/Primitives.h"
#include "mrn/MathSolver.h"
#include "mrn/application/Bifurcation/P.h"
#include "mrn/ui/Widget.h"
#include "mrn/ui/WidgetElement.h"
#include "mrn/engine/common.h"

#include <gtc/matrix_transform.hpp>
#include <glm.hpp>
#include <ext.hpp>

int main() {

    int a = 65539;
    auto v = toBytes(&a);
    int b = fromBytes<int>(v);

    ScreenSize c = ScreenSize { 1024, 768};
    auto w = toBytes(&c);
    ScreenSize d = fromBytes<ScreenSize>(w);
    mrn::P solver = mrn::P();
//    solver.calc();

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



    //////////////////////////////////////////////////////////////////////////////////

    const uint32_t win_width = 1200;
    const uint32_t win_height = 800;
    mrn::Engine* engine = new mrn::Engine();
    engine->createWindow(win_width, win_height);
    engine->createScene();

    mrn::Shader s_default("shader/default_mvp.vert", "shader/default.frag");

    mrn::Model vis = mrn::Model();
    vis.vertex_data = &mesh;
    vis.shader = &s_default;
    mesh.initBuf();
    engine->getScene()->addSceneNode(vis);


    mrn::Model grid = mrn::Model();
    mrn::CoordSystem3D coord_sys = mrn::CoordSystem3D();
    coord_sys.initBuf();
    grid.vertex_data = &coord_sys;
    grid.shader = &s_default;

    engine->getScene()->addSceneNode(grid);
    std::string fps_str;
    int t = 0;
    int t_new = 0;
  //  fontRenderer->setFontSize(16);
    engine->getFontRenderer()->setFont("fonts/arial.ttf");

    // UI
    mrn::ui::Widget* settings = new mrn::ui::Widget("Settings", 0, 0, 0.5, 0.5);
    while(!engine->getWindow()->shouldClose()) {
        t = (int)glfwGetTime();
        if(t > t_new) {
            t_new = t;
            double fps = 1 / engine->getWindow()->getDeltaTime();
            fps_str = std::to_string(fps);
        }
        engine->getFontRenderer()->renderText("FPS: " + fps_str, 0, engine->getWindow()->getHeight() - 32, vec3(1.0, 0, 0));
        engine->getFontRenderer()->renderText("Vertex Count: " + std::to_string(vis.getVertexCount()), 0, 0, vec3(1.0, 1.0, 0.0));
        engine->renderScene();
        engine->processInput();
        settings->render();
        // glfw: poll events & swap buffers
        // --------------------------------
        engine->getEventBus()->notify();
        engine->getWindow()->nextFrame();
        glfwPollEvents();
    }
    return 0;
}