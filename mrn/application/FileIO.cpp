//
// Created by mrn on 19/07/03.
//

#include <fstream>
#include <iostream>
#include "FileIO.h"

FileIO::FileIO() {

}

FileIO::~FileIO() {

}

bool FileIO::writeVertices(string filename, vector<Vertex> &vertices) {
    ofstream file(filename, ios::out);
    if(!file.is_open()) {
        cerr << "Error opening File " << filename << endl;
        exit(1);
    }

    for(Vertex& v : vertices) {
        file << v.pos.x << "\t" << v.pos.y << "\t" << v.pos.z << "\t"
             << v.normal.x << "\t" << v.normal.y << "\t" << v.normal.z << endl;
    }

}
