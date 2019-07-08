//
// Created by Marian Cichy
//

#pragma once


#include <vector>

namespace mrn {

    struct Point2D {
        double x;
        double y;

        Point2D  operator+(const double& n)  {
            Point2D result = {0,0};
            result.x = this->x + n;
            result.y = this->y + n;
            return result;
        }

         Point2D operator+(const Point2D& other)  {
            Point2D result = {0,0};
            result.x = this->x + other.x;
            result.y = this->y + other.y;
            return result;
        }

         Point2D operator*(const double& n)  {
            Point2D result = {0,0};
            result.x = this->x * n;
            result.y = this->y * n;
            return result;
        }

         Point2D operator*( Point2D& other)  {
            Point2D result = {0,0};
            result.x = this->x * other.x;
            result.y = this->y * other.y;
            return result;
        }
    };

    struct parameterSet {
        double k;
        double B0;
        double B;
    };

    class P {
    public:
        Point2D p;
        parameterSet parameter = {.k=0.1, .B0=0.2, .B=0.4};
        double h = 0.1;
        double x[2] = {0.98720931,1.14311277}; // initial value
        double t = 0;
        const double iterations = 10000;

        P();
        ~P();
        void calc();
        Point2D rungeKutta(Point2D p, parameterSet& para, double stepSize, double& time);
        Point2D newton();
        Point2D duffing(Point2D p, parameterSet& para, double t);

        std::vector<Point2D> result;
        std::vector<Point2D> fixpoints;
    };
}

