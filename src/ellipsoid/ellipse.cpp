#include "ellipse.hpp"
#include <Eigen/Core>
#include <iostream>
#include <iomanip>

Ellipse::Ellipse()
{
    semi_axes = {1.0, 1.0};
    ptr_position = nullptr;
    ptr_orientation = nullptr;
}

Ellipse::Ellipse(const double& a, const double& b)
{
    semi_axes = {a, b};
    ptr_position = nullptr;
    ptr_orientation = nullptr;
}

std::array<double, 2> Ellipse::getPositionVector()
{
    if (ptr_position) { return { (*ptr_position)(0), (*ptr_position)(1) }; }
    else { return {0.0, 0.0}; }
}

void Ellipse::setCanonicalTransform()
{
    setPositionVector();
    setRotationMatrix();
}

void Ellipse::setPositionVector()
{
    if (ptr_position) { *ptr_position = Eigen::Vector2d(0.0, 0.0); }
    else { ptr_position = std::make_shared<Eigen::Vector2d>(Eigen::Vector2d(0.0, 0.0)); }
}

void Ellipse::setPositionVector(std::array<double, 2>& position)
{
    Eigen::Vector2d positionVector(position[0], position[1]);
    if (ptr_position) { *ptr_position = positionVector; }
    else { ptr_position = std::make_shared<Eigen::Vector2d>(positionVector); }
}

void Ellipse::setRotationMatrix()
{
    if (ptr_orientation) { *ptr_orientation = Eigen::Matrix2d::Identity(); }
    else { ptr_orientation = std::make_shared<Eigen::Matrix2d>(Eigen::Matrix2d::Identity()); }
}

void Ellipse::setRotationMatrix(std::array<std::array<double, 2>, 2>& rotation)
{
    Eigen::Matrix2d rotationMatrix = Eigen::Map<Eigen::Matrix<double, 2, 2>>(rotation[0].data());
    if (ptr_orientation) { *ptr_orientation = rotationMatrix; }
    else { ptr_orientation = std::make_shared<Eigen::Matrix2d>(rotationMatrix); }
}

void Ellipse::printEllipseTransform() const
{
    printSemiAxes();
    printPositionVector();
    printRotationMatrix();
}

void Ellipse::printSemiAxes() const
{
    std::cout << "Ellipse semi-principal axes lengths:\n";
    std::cout << "a-axis: " << semi_axes[0] << "\n";
    std::cout << "b-axis: " << semi_axes[1] << "\n";
}

void Ellipse::printPositionVector() const
{
    std::cout << "Position vector:\n";
    if (ptr_position) { std::cout << *ptr_position << "\n"; }
    else { std::cout << "Position is null" << "\n"; }
}

void Ellipse::printRotationMatrix() const
{
    std::cout << "Rotation matrix:\n";
    if (ptr_orientation) { std::cout << *ptr_orientation << "\n"; }
    else { std::cout << "Orientation is null" << "\n"; }
}

bool Ellipse::hasTransform() const
{
    return (ptr_position && ptr_orientation);
}

bool Ellipse::isCircle() const
{
    return (semi_axes[0] == semi_axes[1]);
}

