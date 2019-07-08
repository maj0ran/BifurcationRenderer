//
// Created by mrn on 19/06/05.
//

#pragma once

#include <vector>

class Gauss {
public:
    Gauss();
    ~Gauss();

    std::vector<double> gauss(std::vector<std::vector<double>> A);
};
