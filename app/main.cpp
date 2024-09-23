#include <iostream>

#include "config.hpp"
#include "ellipsoid.hpp"
#include <Eigen/Core>

int main()
{
    std::cout << project_name << '\n';
    std::cout << project_version << '\n';

    Ellipsoid ellipsoid = Ellipsoid(6.0, 4.0, 2.0);
    ellipsoid.printEllipsoidTransform();

    ellipsoid.setCanonicalTransform();
    ellipsoid.printEllipsoidTransform();

    
    return 0;
}
