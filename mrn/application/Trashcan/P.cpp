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
                fixpoints.push_back(p);
            //    printf("%f %f\n", p.x, p.y);
            }
            result.push_back(p);
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
//    int newton()
//    {
//        int i;
//        double prev[NN];
//        double h[NN];
//        double a[NN][NN];
//        double b[NN];
//
//        for ( i = 0; i < 2; i++) prev[i] = duf.x[i];
//
//        sysvar();
//
//        a[0][0] = duf.x[2] - 1.0;
//        a[0][1] = duf.x[4];
//        a[0][2] = prev[0] - duf.x[0];
//        a[1][0] = duf.x[3];
//        a[1][1] = duf.x[5] - 1.0;
//        a[1][2] = prev[1] - duf.x[1];
//
//        gauss(2,a,h);
//
//        for ( i = 0; i < 2; i++) duf.x[i] = prev[i] + h[i];
//    }

    Point2D P::newton() {
        int i;
        double prev[2];
        prev[0] = x[0];
        prev[1] = x[1];


        return Point2D();
    }
}