//
// Created by mrn on 19/05/15.
//

#pragma once

// f''(t) + delta*f'(t) + alpha * f(t) + beta * f(t)^3 = gamma * cos(omega * t)

// 2nd Order ODE because there is an f''

// We are looking for f(t) such that the above equation is true

// ---------------------------------------------------------------- //

// 1. Initial Value Problem? We have to find the solution of f(t) for a particular t.
// For example t = 0, we have to find know the value of f(0).

// 2. delta, alpha, gamma and omega are constants for now

// f''(t) + f'(t) + f(t) + f(t)^3 = cos(t)

// Beschleunigung + Geschwindigkeit + Position + Position^3 = Cosinus?



class DuffingSolver {
public:
    DuffingSolver();
    ~DuffingSolver();

    float initial_value = 0;
    float time; // t
    float damping = 1; // delta
    float stiffness = 1; // alpha?
    float amplitude = 1; // gamma
    float frequency = 1; // omega

    // Euler Method
    const float step_size = 0.1f;

};


