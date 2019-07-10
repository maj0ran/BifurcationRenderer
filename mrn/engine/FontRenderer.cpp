//
// Created by Marian Cichy
//

#include <ext.hpp>
#include "FontRenderer.h"
#include "GLVertex.h"
#include "common.h"

namespace mrn {
    FontRenderer::FontRenderer() {
        if (FT_Init_FreeType(&ft)) {
            printf("ERROR::FREETYPE: Could not init FreeType Library\n");
        }

        fontShader = new Shader("shader/font.vert", "shader/font.frag");

        // Initialize Buffer-Objects for Fontrendering
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    FontRenderer::~FontRenderer() {
        FT_Done_Face(face);
        FT_Done_FreeType(ft);
    }

    void FontRenderer::setFont(std::string font_location) {
        if (FT_New_Face(ft, font_location.c_str(), 0, &face)) {
            printf("ERROR::FREETYPE: Failed to load font");
        }

        FT_Set_Pixel_Sizes(face, 0, cur_size);
        loadCharacters();
    }

    void FontRenderer::setFontSize(unsigned int size) {
        cur_size = size;
        if (face != nullptr) {
            FT_Set_Pixel_Sizes(face, 0, cur_size);
        }
    }

    void FontRenderer::loadCharacters() {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

        for (GLubyte c = 0; c < 128; c++) {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                printf("ERROR::FREETYPE: Failed to load Glyph: %d\n", c);
                continue;
            }
            // Generate a texture for each glyph
            GLuint texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                    GL_TEXTURE_2D,
                    0,
                    GL_RED,
                    face->glyph->bitmap.width,
                    face->glyph->bitmap.rows,
                    0,
                    GL_RED,
                    GL_UNSIGNED_BYTE,
                    face->glyph->bitmap.buffer
            );
            // Set texture options

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            // Store the characters for later use
            Character character = {
                    texture,
                    glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                    glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                    face->glyph->advance.x
            };
            this->characters.insert(std::pair<GLchar, Character>(c, character));
        }
    }



    void FontRenderer::renderText(std::string text, GLfloat x, GLfloat y, glm::vec3 color) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



        fontShader->use();
        GLint textColor = glGetUniformLocation(fontShader->id, "textColor");
        glUniform3f(textColor, color.x, color.y, color.z);

        GLint proj_loc = glGetUniformLocation(fontShader->id, "projection");
        glUniformMatrix4fv(proj_loc, 1, GL_FALSE, value_ptr(projection));

        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);

        for(const char& c : text) {
            Character ch = this->characters[c];

            GLfloat xpos = x + ch.bearing.x;
            GLfloat ypos = y - (ch.size.y - ch.bearing.y);

            GLfloat w = ch.size.x;
            GLfloat h = ch.size.y;

            // Update VBO for each caracter
            // I don't use my vertex-struct here, because this is an edge-case where I can increase perfomance
            GLfloat vertices[6][4] = {
                    { xpos,     ypos + h,   0.0, 0.0 },
                    { xpos,     ypos,       0.0, 1.0 },
                    { xpos + w, ypos,       1.0, 1.0 },

                    { xpos,     ypos + h,   0.0, 0.0 },
                    { xpos + w, ypos,       1.0, 1.0 },
                    { xpos + w, ypos + h,   1.0, 0.0 }
            };

            // Render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch.textureId);
            // Update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // Render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            x += (ch.advance >> 6); // Bitshift by 6 to get value in pixels (2^6 = 64)
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_BLEND);
    }

    void FontRenderer::onNotify(Event &e) {
        switch(e.getType()) {
            case WINDOW_RESIZE: {
                ScreenSize size = e.readData<ScreenSize>();
                this->projection = glm::ortho(0.0f, (float) size.width, 0.0f, (float) size.height);
                break;
            }
            default:
                break;

        }



    }

}