//
// Created by Marian Cichy
//

#include "MathSolver.h"

MathSolver::MathSolver() {

}

MathSolver::~MathSolver() {

}

std::vector<std::array<float, 3>> MathSolver::solve() {
    std::vector<std::array<float, 3>> result;

    float x, y, z;
    for(int i = -20; i < 20; i++) {
        z = i / 10.0f;
        for (int j = -20; j < 20; j++) {
            x = j / 10.0f;
            y  = x*x + z*z;
            std::array<float, 3> solution = {x, y, z};
            result.push_back({x, y, z});
        }
    }
    return result;
}
