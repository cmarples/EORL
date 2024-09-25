#ifndef NEWTONRAPHSON_HPP
#define NEWTONRAPHSON_HPP

#include <functional>

double NewtonRaphson(std::function<double(double)> Function, std::function<double(double)> Derivative, double initial_guess);
double SafeNewtonRaphson(std::function<double(double)> Function, std::function<double(double)> Derivative,
                         double lower_limit, double upper_limit, double initial_guess);

#endif // NEWTONRAPHSON_HPP