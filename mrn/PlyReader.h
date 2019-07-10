//
// Created by mrn on 19/07/10.
//

#pragma once
#include <vector>
#include <string>
#include "engine/GLVertex.h"
#include "engine/Mesh.h"

using namespace std;


class PlyReader {
public:
    PlyReader();
    ~PlyReader();

    mrn::Mesh readPlyFile(string filename);
};


