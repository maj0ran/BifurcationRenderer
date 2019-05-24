//
// Created by Marian Cichy
//

#pragma once

#define RED glm::vec3(1.0, 0.0, 0.0)
#define GREEN glm::vec3(0.0, 1.0, 0.0)
#define BLUE glm::vec3(0.0, 0.0, 1.0)

template <typename T>
std::vector<unsigned char> toBytes(T val) {
    std::vector<unsigned char> array;
    for(unsigned int i = 1; i <= sizeof(T); i++) {
        unsigned char b = (unsigned char)(val >> (8 * (sizeof(T) - i)));
        array.push_back(b);
    }
    return array;
}

template <typename T>
T fromBytes(std::vector<unsigned char> array) {
    T val = 0;
    for (unsigned int i = 0; i < array.size(); i++) {
        val += array[i] << (8 * (array.size() - 1 - i));
    }
    return val;
}