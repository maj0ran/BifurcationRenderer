//
// Created by Marian Cichy
//

#include "P.h"
#include <math.h>
#include <cstdio>

namespace mrn {
    void P::calc() {
        Point2D p = {x[0], x[1]};
        double t = 0;
        for (int i = 0; i < iterations; i++) {
            p = rungeKutta(p, parameter, h, t);
            if(t >= 2 * M_PI) {
                t = 0;
            }
            printf("%f %f\n", p.x, p.y);
        }
    }

    Point2D P::rungeKutta(Point2D p, parameterSet& para, double stepSize, double& time) {
        Point2D k1 = duffing(p, para, time);
        Point2D k2 = duffing((p + k1 * (stepSize / 2)), para, time + (stepSize / 2));
        Point2D k3 = duffing((p + k2 * (stepSize / 2)), para, time + (stepSize / 2));
        Point2D k4 = duffing(p + k3 * stepSize, para, time + stepSize);

        Point2D result = (p + (k1 + k2 * 2 + k3 * 2 + k4) * (stepSize / 6));
       // printf("%f %f\n", result.x, result.y);
        time = time + stepSize;
        return result;
    };

    Point2D P::duffing(Point2D p, parameterSet& para, double t) {
        Point2D result;
        result.x = p.y;
        result.y = -para.k * p.y - pow(p.x, 3) + para.B0 + para.B * cos(t);

        return result;
    }

    P::P() {

    }

    P::~P() {

    }
}