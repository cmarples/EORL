#include "ellipsoid.hpp"
#include <iostream>
#include <iomanip>

Ellipsoid::Ellipsoid()
{
    semi_axes = {1.0, 1.0, 1.0};
}

Ellipsoid::Ellipsoid(const double &a, const double &b, const double &c)
{
    semi_axes = {a, b, c};
}

void Ellipsoid::printSemiAxes() const
{
    std::cout << std::fixed << std::setprecision(3);
    std::cout << "Ellipsoid semi-principal axes lengths:\n";
    std::cout << "a-axis: " << semi_axes[0] << "\n";
    std::cout << "b-axis: " << semi_axes[1] << "\n";
    std::cout << "c-axis: " << semi_axes[2] << "\n";
}
