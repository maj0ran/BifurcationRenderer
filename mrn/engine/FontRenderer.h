//
// Created by Marian Cichy
//

#pragma once

#include <string>

#include <glad/glad.h>
#include <glfw3.h>
#include <glm.hpp>
#include <ft2build.h>

#include <map>
#include FT_FREETYPE_H
#include "Shader.h"
#include "eventbus/BusNode.h"

namespace mrn {
    struct Character {
        GLuint textureId;
        glm::ivec2 size;
        glm::ivec2 bearing;
        long advance;
    };

    class FontRenderer : public BusNode {
    public:
        FontRenderer();
        ~FontRenderer();

        void setFont(std::string font_location);
        void setFontSize(unsigned int size);

        void renderText(std::string text, GLfloat x, GLfloat y, glm::vec3 color);

    private:
        FT_Library ft;
        FT_Face face;

        GLuint VAO, VBO;
        Shader* fontShader;
        glm::mat4 projection = glm::ortho(0.0f, 1200.0f, 0.0f, 800.0f);

        std::map<GLchar, Character> characters;
        unsigned int cur_size = 32;

        void loadCharacters();

        void onNotify(Event &e) override;

    };

}
