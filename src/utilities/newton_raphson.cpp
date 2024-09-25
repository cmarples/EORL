#include "newton_raphson.hpp"
#include <cmath>
#include <cassert>

double NewtonRaphson(std::function<double(double)> Function, std::function<double(double)> Derivative, double initial_guess)
{
    double tolerance = 1e-14;
    double x_difference = 1.0;
    double y_difference = 1.0;
    double new_function_value;
    double function_value = Function(initial_guess);
    double x_value = initial_guess;

    while (fabs(x_difference) > tolerance && fabs(y_difference) > tolerance) 
    {
        x_difference = function_value / Derivative(x_value);
        x_value -= x_difference;
        new_function_value = Function(x_value);
        y_difference = new_function_value - function_value;
        function_value = new_function_value;
    }

    return x_value;
}

double SafeNewtonRaphson(std::function<double(double)> Function, std::function<double(double)> Derivative, double lower_limit, double upper_limit, double initial_guess)
{
    int max_iterations = 100;
    double tolerance = 1e-14;
    double x_difference = 1.0;
    double previous_x_difference = 1.0;

    // Assuming that aFun = f(a) and bFun = f(b) have opposite signs (so a root lies between them)
    double function_value_lower_limit = Function(lower_limit);
    double function_value_upper_limit = Function(upper_limit);
    assert(function_value_lower_limit * function_value_upper_limit <= 0);

    double x_lower;
    double x_upper;
    if (function_value_lower_limit < 0) 
    {
        x_lower = lower_limit;
        x_upper = upper_limit;
    }
    else 
    {
        x_upper = lower_limit;
        x_lower = upper_limit;
    }

    double x_value = initial_guess;
    double function_value = Function(x_value);
    double derivative_value = Derivative(x_value);

    for (int k = 0; k < max_iterations; k++) 
    {
        // Use bisection if Newton-Raphson out of range, or if convergence too slow
        // Else, use Newton-Raphson
        if ((((x_value - x_upper) * derivative_value - function_value) * ((x_value - x_lower) * derivative_value - function_value) >= 0) ||
            abs(2 * function_value) > abs(previous_x_difference * derivative_value)) 
        {
            previous_x_difference = x_difference;
            x_difference = 0.5 * (x_upper - x_lower);
            x_value = x_lower + x_difference;
        }
        else 
        {
            previous_x_difference = x_difference;
            x_difference = function_value / derivative_value;
            x_value -= x_difference;
        }

        // Check for convergence
        if (fabs(x_difference) < tolerance) { break; }

        function_value = Function(x_value);
        derivative_value = Derivative(x_value);

        // Define new interval
        if (function_value < 0) { x_lower = x_value; }
        else { x_upper = x_value; }
    }

    return x_value;
}


