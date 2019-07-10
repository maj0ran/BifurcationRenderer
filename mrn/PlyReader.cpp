//
// Created by mrn on 19/07/10.
//

#include "PlyReader.h"
#include "engine/GLVertex.h"

#include <fstream>
#include <iostream>
#include <sstream>

PlyReader::PlyReader() {

}

PlyReader::~PlyReader() {

}

mrn::Mesh PlyReader::readPlyFile(string filename) {
    mrn::Mesh mesh;

    ifstream file(filename, ios::in);
    if (!file.is_open()) {
        cerr << "Error opening file " << filename << endl;
        exit(1);
    }
    std::string vertex_count_line = "element vertex";
    std::string end_header = "end_header";
    std::string line;
    int vertex_count = 0;

    // first we look for the line "element vertex" to extract the number of vertices
    while(std::getline(file, line)) {
        if(line.find(vertex_count_line) != std::string::npos) {
            std::stringstream ss;
            ss << line;
            std::string temp;
            while(!ss.eof()) {
                ss >> temp;
                if(stringstream(temp) >> vertex_count)
                    break;
            }
            break;
        }
    }

    // then we move to the end of the header which is denoted by "end_header"
    while(std::getline(file, line)) {
        if(line.find(end_header) != std::string::npos) {
            break;
        }
    }

    // now we read *vertex_count* number of vertices
    float x, y, z; // vertex pos
    float nx, ny, nz; // vertex normal
    for(int i = 0; i < vertex_count; i++) {
        file >> x >> y >> z >> nx >> ny >> nz;
        mrn::GLVertex vertex;
        vertex.pos = vec3(x,y,z);
        vertex.normal = vec3(nx, ny, nz);
        mesh.addVertex(vertex);
    }

    // everything from here until EOF are the indices
    int n, i1, i2, i3;
    while(std::getline(file, line)) {
        if(line.empty()) // error check because txt files like to have an empty last line
            continue;

        std::stringstream ss;
        ss << line;
        ss >> n >> i1 >> i2 >> i3;
        mesh.addIndex(i1);
        mesh.addIndex(i2);
        mesh.addIndex(i3);
    }

    mesh.setPatchSize(3);

  return mesh;
}
