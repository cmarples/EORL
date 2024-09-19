#include "ellipsoid.hpp"
#include <Eigen/Core>
#include <iostream>
#include <iomanip>

Ellipsoid::Ellipsoid()
{
    semi_axes = {1.0, 1.0, 1.0};
    ptr_position = nullptr;
    ptr_orientation = nullptr;
}

Ellipsoid::Ellipsoid(const double &a, const double &b, const double &c)
{
    semi_axes = {a, b, c};
    ptr_position = nullptr;
    ptr_orientation = nullptr;
}

void Ellipsoid::setCanonicalTransform()
{
    ptr_position = std::make_shared<Eigen::Vector3d>(Eigen::Vector3d(0.0, 0.0, 0.0));
    ptr_orientation = std::make_shared<Eigen::Matrix3d>(Eigen::Matrix3d::Identity());
}

void Ellipsoid::setPositionVector()
{
    ptr_position = std::make_shared<Eigen::Vector3d>(Eigen::Vector3d(0.0, 0.0, 0.0));
}

void Ellipsoid::setRotationMatrix()
{
    ptr_orientation = std::make_shared<Eigen::Matrix3d>(Eigen::Matrix3d::Identity());
}

void Ellipsoid::printEllipsoidTransform() const
{
    printSemiAxes();
    printPositionVector();
    printRotationMatrix();
}

void Ellipsoid::printSemiAxes() const
{
    std::cout << "Ellipsoid semi-principal axes lengths:\n";
    std::cout << "a-axis: " << semi_axes[0] << "\n";
    std::cout << "b-axis: " << semi_axes[1] << "\n";
    std::cout << "c-axis: " << semi_axes[2] << "\n";
}

void Ellipsoid::printPositionVector() const
{
    std::cout << "Position vector:\n";
    if (ptr_position) { std::cout << *ptr_position << "\n"; }
    else { std::cout << "Position is null" << "\n"; }
}

void Ellipsoid::printRotationMatrix() const
{
    std::cout << "Rotation matrix:\n";
    if (ptr_orientation) { std::cout << *ptr_orientation << "\n"; }
    else { std::cout << "Orientation is null" << "\n"; }
}

bool Ellipsoid::hasTransform() const
{
    return (ptr_position && ptr_orientation);
}
