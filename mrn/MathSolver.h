//
// Created by Marian Cichy
//

#pragma once

#include <vector>
#include <array>

class MathSolver {
public:
    MathSolver();
    ~MathSolver();

    // f(x,y,z) = 0
    // f = x^2 + y^2 - z = 0
    // x^2 + y^2 = z;
    std::vector<std::array<float, 3>> solve();

};


