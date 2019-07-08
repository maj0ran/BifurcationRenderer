//
// Created by mrn on 19/06/13.
//

#include "Bifurcation.h"

#include <fstream>
#include <iostream>
#include "../../../3rdparty/delaunay/delaunator.hpp"

#include "../../3rdparty/Eigen/Eigen"

Bifurcation::Bifurcation() {

}

Bifurcation::~Bifurcation() {

}

void Bifurcation::read(vector<const char *> &filenames) {
    double k = 0.2;
    for (auto filename : filenames) {
        ifstream file(filename, ios::in);
        if (!file.is_open()) {
            cerr << "Error opening file " << filename << endl;
            exit(1);
        }

        vector<double> line;
        double val = 0.0;
        while (file >> val) {
            line.push_back(val);
            if (file.peek() == '\n') {
                bifurcationData.push_back(Vertex { vec3(line[0], line[1], line[2]), vec3(0,0,0)});
                line.clear();
            }
        }
        file.close();
        k += 0.0005;
    }
    scale(1000.0);
}




/*
 * Subtract out the centroid, form a 3×N matrix X out of the resulting coordinates
 * and calculate its singular value decomposition.
 * The normal vector of the best-fitting plane is the left singular vector corresponding
 * to the least singular value.
 */
void Bifurcation::estimateNormal(int point) {

    vector<int> neighborIndex = getNeighbors(point, 10);
    vector<Vertex> neighborPoints;
    for(int i : neighborIndex) {
        neighborPoints.push_back(bifurcationData[i]);
    }

    // Calculate the mean of the points
    Vertex centroid = getCentroid(&neighborPoints);

    Eigen::MatrixXf M(3,neighborIndex.size());
    for(int i = 0; i < neighborIndex.size(); i++) {
        M(0, i) = neighborPoints[i].pos.x - centroid.pos.x;
        M(1, i) = neighborPoints[i].pos.y - centroid.pos.y;
        M(2, i) = neighborPoints[i].pos.z - centroid.pos.z;
    }

    Eigen::JacobiSVD<Eigen::MatrixXf> svd(M, Eigen::ComputeThinU);

    int correspondingValue = 0;
    for(int i = 0; i < svd.singularValues().size(); i++) {
        double smallest = std::numeric_limits<double>::infinity();
        if(svd.singularValues()[i] < smallest) {
            smallest = svd.singularValues()[i];
            correspondingValue = i;
        }
    }
    vec3 normal(svd.matrixU().col(correspondingValue)[0],
                   svd.matrixU().col(correspondingValue)[1],
                   svd.matrixU().col(correspondingValue)[2]
                   );

    bifurcationData[point].normal = vec3(normal.x, normal.y, normal.z);
    bifurcationData[point].normal /= 0.1;


}

Vertex Bifurcation::getCentroid(vector<Vertex>* points) {
    Vertex centroid = {vec3(0, 0, 0), vec3(0,0,0)};
    for (int i = 0; i < points->size(); i++) {
        centroid.pos.x += (*points)[i].pos.x;
        centroid.pos.y += (*points)[i].pos.y;
        centroid.pos.z += (*points)[i].pos.z;
    }
    centroid.pos.x /= points->size();
    centroid.pos.y /= points->size();
    centroid.pos.z /= points->size();

    return centroid;
}

vector<int> Bifurcation::getNeighbors(int center, double r) {

    vector<int> indecesOfNeighbors;
    for(int p = 0; p < bifurcationData.size(); p++) {
        double distance = sqrt(
                pow(bifurcationData[center].pos.x - bifurcationData[p].pos.x, 2) +
                pow(bifurcationData[center].pos.y - bifurcationData[p].pos.y, 2) +
                pow(bifurcationData[center].pos.z - bifurcationData[p].pos.z, 2)
                );
        if(distance < r) {
            indecesOfNeighbors.push_back(p);
        }
    }
    return indecesOfNeighbors;
}

Vertex Bifurcation::getPointByIndex(int index) {
    return bifurcationData[index];
}

void Bifurcation::correctNormalDirection() {
    int i = 0;
    Vertex center = getCentroid(&bifurcationData);
    for(Vertex& p : bifurcationData) {
        if(length(center.pos - (p.normal + p.pos)) < length(center.pos - p.pos)) {
            i++;
            p.normal *= -1;
        }
    }
}

void Bifurcation::scale(float factor) {
    for(Vertex& p : bifurcationData) {
        p.pos *= factor;
    }
}

void Bifurcation::estimateNormals() {
    for(int i = 0; i < bifurcationData.size(); i++) {
        estimateNormal(i);
    }
}
