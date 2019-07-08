#include <iostream>

#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <cmath>

#include "mrn/engine/Engine.h"
#include "mrn/engine/TriangleIndex.h"
#include "mrn/engine/Window.h"
#include "mrn/engine/FontRenderer.h"
#include "mrn/engine/Vertex.h"
#include "mrn/engine/Line.h"
#include "mrn/engine/Model.h"
#include "mrn/engine/Scene.h"
#include "mrn/application/CoordSystem3D.h"
#include "mrn/engine/Primitives.h"
#include "mrn/MathSolver.h"
#include "mrn/application/Trashcan/P.h"
#include "mrn/engine/common.h"
#include "mrn/application/Interface.h"
#include "mrn/application/Bifurcation/Bifurcation.h"
#include "3rdparty/Eigen/Dense"
#include "mrn/application/Bifurcation/Mesher.h"
#include "mrn/application/Bifurcation/Triangle.h"
#include "mrn/Debug.h"

#include <gtc/matrix_transform.hpp>
#include <glm.hpp>
#include <ext.hpp>
#include "mrn/application/FileIO.h"

#include <vector>
#include "mrn/application/Bifurcation/ballpivot/Mesher.h"
int main() {
    const uint32_t win_width = 1200;
    const uint32_t win_height = 800;
    mrn::Engine* engine = new mrn::Engine();
    engine->createWindow(win_width, win_height);
    engine->createScene();
    glPointSize(6);
    mrn::Shader s_default("shader/default_mvp.vert", "shader/default.frag");





    //////////////////////////////////////////////////////////////////////////////////



    mrn::Model grid = mrn::Model();
    mrn::CoordSystem3D coord_sys = mrn::CoordSystem3D();
    grid.vertex_data = &coord_sys;
    grid.shader = &s_default;
    grid.initBuf();

    engine->getScene()->addSceneNode(grid);

  //  fontRenderer->setFontSize(16);
    engine->getFontRenderer()->setFont("fonts/arial.ttf");

    // UI
    Interface* interface = new Interface(engine->getWindow()->getGlfwWindowPtr());
    ImGuiIO& io = ImGui::GetIO();
    const float font_size = 18;
    io.Fonts->AddFontFromFileTTF("fonts/consola.ttf", font_size);
    // Render Loop
    float k = 0.2;
    float B = 0.2;
    float B0 = 0.4;
    float stepsize = 0.01;

    ImGui::StyleColorsLight();

    vector<const char*> filenames;
    filenames.push_back("data/fixed_i1k02.txt");
    filenames.push_back("data/fixed_i1k0205.txt");
    filenames.push_back("data/fixed_i1k021.txt");

    Bifurcation bif;
    bif.read(filenames);
    Mesher pivoter(bif.bifurcationData);
    pivoter.reconstruct();
    mrn::Mesh bifurcationPoints;
    for(auto p : pivoter.getPoints()) {
        mrn::GLVertex v;
        v.pos = {p.pos.x, p.pos.y, p.pos.z};
        if(p.state == VERTEXSTATE_FRONT)
            v.rgb = GREEN;
        else if(p.state == VERTEXSTATE_ORPHAN)
            v.rgb = PINK;
        else if(p.state == VERTEXSTATE_INNER)
            v.rgb = ORANGE;
        bifurcationPoints.addVertex(v);
    }
    mrn::Model bifurcationPointsModel(&bifurcationPoints, &s_default);
  //  bpa::Mesher* bpa_mesher = new bpa::Mesher();
    //bpa_mesher.
    mrn::Mesh bifurcationNormals;
    bif.estimateNormals();
    bif.correctNormalDirection();
    FileIO file_io;
    file_io.writeVertices("bif_vertices.txt", bif.bifurcationData);

    for(int i = 0; i < bif.bifurcationData.size(); i++) {
        mrn::GLVertex n1;
        n1.pos = bif.bifurcationData[i].pos;
        n1.rgb = vec3(0, 1, 1);
        mrn::GLVertex n2;
        n2.pos = bif.bifurcationData[i].normal + bif.bifurcationData[i].pos;
        n2.rgb = vec3(0, 1, 1);
        bifurcationNormals.addVertex(n1);
        bifurcationNormals.addVertex(n2);
    }


    mrn::Model bifurcationNormalsModel(&bifurcationNormals, &s_default);





  //  engine->getScene()->addSceneNode(duffModel);

    mrn::Mesh recon;

    for(Triangle& t : pivoter.reconstructedSurface->triangles()) {
        for(Vertex* v : t.points) {
            mrn::GLVertex glv;
       //     printf("Vertex State: %d\n", v->state);
            if(v->state == VERTEXSTATE_FRONT) {
                glv = mrn::GLVertex(*v, GREEN);
            }
            if(v->state == VERTEXSTATE_INNER) {
                glv = mrn::GLVertex(*v, YELLOW);
            }
            if(v->state == VERTEXSTATE_ORPHAN) {
                glv = mrn::GLVertex(*v, BLUE);
            }
            recon.addVertex(glv);
        }
    }

    Debug dbg = pivoter.getDebugger();
    dbg.toVram();

    mrn::Model reconModel;
    reconModel.shader = &s_default;
    reconModel.vertex_data = &recon;
    reconModel.initBuf();
    while(!engine->getWindow()->shouldClose()) {
        // Bifurcation Points
        bifurcationPointsModel.bind();
        glDrawArrays(GL_POINTS, 0, bifurcationPointsModel.getVertexCount());
        // Vertex Normals
        bifurcationNormalsModel.bind();
        glDrawArrays(GL_LINES, 0, bifurcationNormalsModel.getVertexCount());
        engine->renderScene();
        engine->processInput();


        /* ---------------------------------------------- */
        dbg.draw();
        reconModel.bind();
        glDrawArrays(GL_TRIANGLES, 0, reconModel.getVertexCount());

        // BEGIN GUI
        interface->startFrame();
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(400, 170));
        ImGui::Begin("Settings:");
        ImGui::Text("k:  ");
        ImGui::SameLine();
        ImGui::InputFloat("##k",&k);
        ImGui::SameLine();
        if(ImGui::Button("<<##k_dec")) { k -= stepsize; }
        ImGui::SameLine();
        if(ImGui::Button(">>##k_inc")) { k += stepsize; }

        ImGui::Text("B:  ");
        ImGui::SameLine();
        ImGui::InputFloat("##B",&B);
        ImGui::SameLine();
        if(ImGui::Button("<<##B_dec")) { B -= stepsize; }
        ImGui::SameLine();
        if(ImGui::Button(">>##B_inc")) { B += stepsize; }

        ImGui::Text("B0: ");
        ImGui::SameLine();
        ImGui::InputFloat("##B0",&B0);
        ImGui::SameLine();
        if(ImGui::Button("<<##B0_dec")) { B0 -= stepsize; }
        ImGui::SameLine();
        if(ImGui::Button(">>##B0_inc")) { B0 += stepsize; }

        ImGui::Text("FPS: %.3f", ImGui::GetIO().Framerate);

        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // END GUI


        // glfw: poll events & swap buffers
        // --------------------------------

        glfwPollEvents();
        engine->getEventBus()->notify();
        engine->getWindow()->nextFrame();
    }
    return 0;
}