#include <iostream>

#include "config.hpp"
#include "ellipsoid.hpp"

int main()
{
    std::cout << project_name << '\n';
    std::cout << project_version << '\n';

    Ellipsoid ellipsoid = Ellipsoid(3.0, 2.0, 1.0);
    ellipsoid.printSemiAxes();

    return 0;
}
