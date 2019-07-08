//
// Created by mrn on 19/07/03.
//

#pragma once

#include <vector>
#include <string>
#include "Bifurcation/Vertex.h"
class FileIO {
public:
    FileIO();
    ~FileIO();

    bool writeVertices(string filename, vector<Vertex>& vertices);
};


