//
// Created by Marian Cichy
//
#pragma once

#include <malloc.h>
#include <cstring>

typedef unsigned char byte;

#define RED glm::vec3(1.0, 0.0, 0.0)
#define GREEN glm::vec3(0.0, 1.0, 0.0)
#define BLUE glm::vec3(0.0, 0.0, 1.0)



struct ScreenSize {
    int width;
    int height;
};

struct KeyEvent {
    int key;
    int scancode;
    int action;
    int mods;
};

template <typename T>
byte* toBytes(T* data) {
    byte* result = (byte*)malloc(sizeof(T));
    memcpy(result, data, sizeof(T));
    return result;
}

template <typename T>
T fromBytes(byte* data) {
    T result;
    memcpy(&result, data, sizeof(T));
    return result;
}
