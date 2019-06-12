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
#include "mrn/application/Bifurcation/DataReader.h"

#include <gtc/matrix_transform.hpp>
#include <glm.hpp>
#include <ext.hpp>

int main() {
    const uint32_t win_width = 1200;
    const uint32_t win_height = 800;
    mrn::Engine* engine = new mrn::Engine();
    engine->createWindow(win_width, win_height);
    engine->createScene();

    mrn::Shader s_default("shader/default_mvp.vert", "shader/default.frag");

    mrn::P solver = mrn::P();
    solver.calc();
    glLineWidth(1);

    mrn::Mesh* duffing = new mrn::Mesh();
    for(int i = 0;  i < solver.result.size(); i++) {
        float x = solver.result[i].x;
        float y = solver.result[i].y;
    //    printf("%f %f\n", solver.result[i].x, solver.result[i].y);
        mrn::Vertex v;
        v.pos = vec3(x, y, 0);
        v.rgb = RED;
        duffing->addVertex(v);

    }

    mrn::Model duffingModel = mrn::Model();
    duffingModel.vertex_data = duffing;
    duffingModel.shader = &s_default;
    duffingModel.initBuf();

    mrn::Mesh* fixedPoints = new mrn::Mesh();
    for(int i = 0; i < solver.fixpoints.size(); i++) {
        float x = solver.fixpoints[i].x;
        float y = solver.result[i].y;
        mrn::Vertex v;
        v.pos = vec3(x, y, 0);
        v.rgb = BLUE;
        fixedPoints->addVertex(v);
    }

    mrn::Model fixedPointModel = mrn::Model();
    fixedPointModel.vertex_data = fixedPoints;
    fixedPointModel.shader = &s_default;
    fixedPointModel.initBuf();




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
    DataReader data  = DataReader();


    auto duffing_data = data.read(filenames);
    for(int i = 0; i < duffing_data.size(); i++) {
        for(int j = 0; j < duffing_data[0].size(); j++) {
            for(int k = 0; k < duffing_data[0][0].size(); k++) {
                printf("%f ", duffing_data[i][j][k]);
            }
            printf("\n");
        }
        printf("\n-----------------\n");
    }
    mrn::Mesh duffMesh;
    for(int i = 0; i < duffing_data[0].size(); i++) {
        mrn::Vertex v;
        v.pos = vec3(0.0, duffing_data[0][i][0], duffing_data[0][i][1]);
        v.rgb = RED;
        duffMesh.addVertex(v);
    }


    for(int i = 0; i < duffing_data[1].size(); i++) {
        mrn::Vertex v;
        v.pos = vec3(0.005, duffing_data[1][i][0], duffing_data[1][i][1]);
        v.rgb = GREEN;
        duffMesh.addVertex(v);
    }




    for (int i = 0; i < duffMesh.vertices.size() - 1; ++i) {
        if(abs(duffMesh.vertices[i + 1].pos.x - 0.0) > 0.001) {
            printf("%f\n", duffMesh.vertices[i].pos.x);
            break;
        }
        // we select 2 neighboring points on the current K-Layer
        uint32_t p1 = i;
        uint32_t p2 = i + 1;
        // then we search for the nearest point on the K+1-Layer
        uint32_t p3 = 0;
        uint32_t p4 = 0;
        double d = std::numeric_limits<double>::infinity();
        for (int j = 0; j < duffMesh.vertices.size(); ++j) {
            if (abs(duffMesh.vertices[j].pos.x - 0.005) < 0.001) {
                double d_current = sqrt
                        (pow(duffMesh.vertices[p1].pos.y - duffMesh.vertices[j].pos.y, 2) +
                         pow(duffMesh.vertices[p1].pos.z - duffMesh.vertices[j].pos.z, 2));
                if (d_current < d) {
                    d = d_current;
                    p3 = j;
                }
            }
        }
        d = std::numeric_limits<double>::infinity();
        for (int j = 0; j < duffMesh.vertices.size(); ++j) {
            if (abs(duffMesh.vertices[j].pos.x - 0.005) < 0.001) {
                double d_current = sqrt
                        (pow(duffMesh.vertices[p2].pos.y - duffMesh.vertices[j].pos.y, 2) +
                         pow(duffMesh.vertices[p2].pos.z - duffMesh.vertices[j].pos.z, 2));
                if (d_current < d && j != p3) {
                    d = d_current;
                    p4 = j;
                }
            }
        }
        duffMesh.addTriangleIndices(p1, p2, p3);
        vec3 n1 = vec3(cross(duffMesh.vertices[p1].pos, duffMesh.vertices[p2].pos));
        duffMesh.addTriangleIndices(p2, p3, p4);
    }

    duffMesh.use_indices = true;

    mrn::Model duffModel;
    duffModel.vertex_data = &duffMesh;
    duffModel.shader = &s_default;
    duffModel.initBuf();
    engine->getScene()->addSceneNode(duffModel);

    while(!engine->getWindow()->shouldClose()) {
    //    bifModel_k02.bind();
    //   glDrawArrays(GL_LINE_STRIP, 0, bifModel_k02.getVertexCount());
    //    bifModel_k0205.bind();
    //    glDrawArrays(GL_LINE_STRIP, 0, bifModel_k0205.getVertexCount());
    //   duffModel.bind();
      //  glDrawArrays(GL_LINE_STRIP, 0, duffModel.getVertexCount());
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