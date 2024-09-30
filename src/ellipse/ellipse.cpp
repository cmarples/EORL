#include "ellipse.hpp"
#include <iostream>
#include <iomanip>

Ellipse::Ellipse()
{
    semi_axes = {1.0, 1.0};
    position = Eigen::Vector2d(0.0, 0.0);
    orientation = Eigen::Matrix2d::Identity();
}

Ellipse::Ellipse(const double& a, const double& b)
{
    semi_axes = {a, b};
    position = Eigen::Vector2d(0.0, 0.0);
    orientation = Eigen::Matrix2d::Identity();
}

Eigen::Vector2d Ellipse::getPositionVector()
{
    return position;
}

void Ellipse::setCanonicalTransform()
{
    setPositionVector();
    setRotationMatrix();
}

void Ellipse::setPositionVector()
{
    position = Eigen::Vector2d(0.0, 0.0);
}

void Ellipse::setPositionVector(float x_coordinate, float y_coordinate)
{
    position = Eigen::Vector2d(x_coordinate, y_coordinate);
}

void Ellipse::setPositionVector(std::array<double, 2>& input_position)
{
    position = Eigen::Vector2d(input_position[0], input_position[1]);
}

void Ellipse::setPositionVector(Eigen::Vector2d &input_position)
{
    position = input_position;
}

void Ellipse::setRotationMatrix()
{
    orientation = Eigen::Matrix2d::Identity();
}

void Ellipse::setRotationMatrix(std::array<std::array<double, 2>, 2>& input_rotation)
{
    orientation = Eigen::Map<Eigen::Matrix<double, 2, 2>>(input_rotation[0].data());
}

void Ellipse::setRotationMatrix(Eigen::Matrix2d &input_rotation)
{
    orientation = input_rotation;
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
    std::cout << position << "\n";
}

void Ellipse::printRotationMatrix() const
{
    std::cout << "Rotation matrix:\n";
    std::cout << orientation << "\n";
}

bool Ellipse::hasTransform() const
{
    return (position != Eigen::Vector2d(0.0, 0.0) ||
         orientation != Eigen::Matrix2d::Identity());
}

bool Ellipse::isCircle() const
{
    return (semi_axes[0] == semi_axes[1]);
}

