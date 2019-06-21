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
#include "mrn/application/Bifurcation/P.h"
#include "mrn/engine/common.h"
#include "mrn/application/Interface.h"
#include "mrn/application/Bifurcation/Bifurcation.h"
#include "3rdparty/Eigen/Dense"
#include "mrn/application/Bifurcation/Pivoter.h"
#include "mrn/application/Bifurcation/Triangle.h"

#include <gtc/matrix_transform.hpp>
#include <glm.hpp>
#include <ext.hpp>

int main() {
    const uint32_t win_width = 1200;
    const uint32_t win_height = 800;
    mrn::Engine* engine = new mrn::Engine();
    engine->createWindow(win_width, win_height);
    engine->createScene();
    glPointSize(2);
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
    filenames.push_back("data/i_1_k=0.2");
    filenames.push_back("data/i_1_k=0.205");

    Bifurcation bif;
    bif.read(filenames);
    Pivoter pivoter;
    auto sorted = pivoter.sortbyDistance(bif.bifurcationData);
    for(int i = 0; i < sorted.size(); i++) {
        printf("%f %f %f << %d \n", sorted[i].pos.x, sorted[i].pos.y, sorted[i].pos.z, i);
    }

    mrn::Mesh bifurcationPoints;
    for(auto p : bif.bifurcationData) {
        mrn::Vertex v;
        v.pos = {p.pos.x, p.pos.y, p.pos.z};
        v.rgb = RED;
        bifurcationPoints.addVertex(v);
    }
    mrn::Model bifurcationPointsModel;
    bifurcationPointsModel.vertex_data = &bifurcationPoints;
    bifurcationPointsModel.shader = &s_default;
    bifurcationPointsModel.initBuf();

    mrn::Mesh bifurcationNormals;
    for(int i = 0; i < bif.bifurcationData.size(); i++) {
        vec3 nStart(bif.bifurcationData[i].pos);
        mrn::Vertex v1;
        v1.pos = nStart;
        v1.rgb = vec3(0, 1, 1);
        bifurcationNormals.addVertex(v1);
        vec3 normal = bif.estimateNormal(i);
        vec3 nEnd(bif.bifurcationData[i].normal);
        normalize(nEnd);
        nEnd.x /= 100.0;
        nEnd.y /= 100.0;
        nEnd.z /= 100.0;
        mrn::Vertex v2;
        v2.pos = {nEnd.x + nStart.x, nEnd.y + nStart.y, nEnd.z + nStart.z};
       // normalize(v2.pos);
        v2.rgb = vec3(0, 1, 1);
        bifurcationNormals.addVertex(v2);
    }

    mrn::Model bifurcationNormalsModel;
    bifurcationNormalsModel.vertex_data = &bifurcationNormals;
    bifurcationNormalsModel.shader = &s_default;
    bifurcationNormalsModel.initBuf();

    auto c = pivoter.circumcenter(&sorted[0], &sorted[1], &sorted[11]);
    printf("%f %f %f :: %f",c.center.x, c.center.y, c.center.z, c.radius);

    Triangle t = pivoter.findSeedTriangle(bif.bifurcationData);
    printf("[%f %f %f :: %f %f %f :: %f %f %f\n", t.points[0].pos.x, t.points[0].pos.y, t.points[0].pos.z,
                                                t.points[1].pos.x, t.points[1].pos.y, t.points[1].pos.z,
                                                t.points[2].pos.x, t.points[2].pos.y, t.points[2].pos.z);
    auto center = bif.getCentroid(bif.bifurcationData);
    printf("%f %f %f\n", center.pos.x, center.pos.y, center.pos.z);
    bif.correctNormalDirection();

  //  engine->getScene()->addSceneNode(duffModel);

    while(!engine->getWindow()->shouldClose()) {
        // Bifurcation Points
        bifurcationPointsModel.bind();
        glDrawArrays(GL_POINTS, 0, bifurcationPointsModel.getVertexCount());
        // Vertex Normals
        bifurcationNormalsModel.bind();
        glDrawArrays(GL_LINES, 0, bifurcationNormalsModel.getVertexCount());
        engine->renderScene();
        engine->processInput();
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