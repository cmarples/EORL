#include "ellipsoid.hpp"
#include <Eigen/Core>
#include <iostream>
#include <iomanip>

Ellipsoid::Ellipsoid()
{
    semi_axes = {1.0, 1.0, 1.0};
    ptr_position = nullptr;
    ptr_orientation = nullptr;
    form = EllipsoidForm::Sphere;
}

Ellipsoid::Ellipsoid(const double &a, const double &b, const double &c)
{
    semi_axes = {a, b, c};
    ptr_position = nullptr;
    ptr_orientation = nullptr;
    determineForm();
}

std::array<double, 3> Ellipsoid::getPositionVector()
{
    if (ptr_position) { return { (*ptr_position)(0), (*ptr_position)(1), (*ptr_position)(2) }; }
    else { return {0.0, 0.0, 0.0}; }
}

void Ellipsoid::setA(double a_axis)
{
    semi_axes[0] = a_axis;
    determineForm();
}

void Ellipsoid::setB(double b_axis)
{
    semi_axes[1] = b_axis;
    determineForm();
}

void Ellipsoid::setC(double c_axis)
{
    semi_axes[2] = c_axis;
    determineForm();
}

void Ellipsoid::setSemiAxes(std::array<double, 3> axes)
{
    semi_axes = axes;
    determineForm();
}

void Ellipsoid::setCanonicalTransform()
{
    setPositionVector();
    setRotationMatrix();
}

void Ellipsoid::setPositionVector()
{
    if (ptr_position) { *ptr_position = Eigen::Vector3d(0.0, 0.0, 0.0); }
    else { ptr_position = std::make_shared<Eigen::Vector3d>(Eigen::Vector3d(0.0, 0.0, 0.0)); } 
}

void Ellipsoid::setPositionVector(std::array<double, 3>& position)
{
    Eigen::Vector3d positionVector(position[0], position[1], position[2]);
    if (ptr_position) { *ptr_position = positionVector; }
    else { ptr_position = std::make_shared<Eigen::Vector3d>(positionVector); } 
}

void Ellipsoid::setRotationMatrix()
{
    if (ptr_orientation) { *ptr_orientation = Eigen::Matrix3d::Identity(); }
    else { ptr_orientation = std::make_shared<Eigen::Matrix3d>(Eigen::Matrix3d::Identity()); }
    
}

void Ellipsoid::setRotationMatrix(std::array<std::array<double, 3>, 3>& rotation)
{
    Eigen::Matrix3d rotationMatrix = Eigen::Map<Eigen::Matrix<double, 3, 3>>(rotation[0].data());
    if (ptr_orientation) { *ptr_orientation = rotationMatrix; }
    else { ptr_orientation = std::make_shared<Eigen::Matrix3d>(rotationMatrix); }
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

bool Ellipsoid::isSphere() const
{
    return semi_axes[0] == semi_axes[1] &&
           semi_axes[1] == semi_axes[2];
}

bool Ellipsoid::isTriaxial() const
{
    return semi_axes[0] != semi_axes[1] && 
           semi_axes[1] != semi_axes[2] && 
           semi_axes[0] != semi_axes[1];
}

bool Ellipsoid::isSpheroid() const
{
    return (semi_axes[0] == semi_axes[1] && semi_axes[0] != semi_axes[2]) ||
           (semi_axes[0] == semi_axes[2] && semi_axes[0] != semi_axes[1]) ||
           (semi_axes[1] == semi_axes[2] && semi_axes[1] != semi_axes[0]);
}

bool Ellipsoid::isOblate()
{
    if (!isSpheroid()) return false;

    SpheroidAxes axes = determineSpheroidAxes();
    if (axes.repeated > axes.distinct) { return true; }
    else { return false; }
}

bool Ellipsoid::isProlate()
{
    if (!isSpheroid()) return false;

    SpheroidAxes axes = determineSpheroidAxes();
    if (axes.repeated < axes.distinct) { return true; }
    else { return false; }
}

void Ellipsoid::determineForm()
{
    if (isSphere()) { form = EllipsoidForm::Sphere; }
    else if (isTriaxial()) { form = EllipsoidForm::Triaxial; }
    else
    {
        if (isOblate()) { form = EllipsoidForm::Oblate; }
        else { form = EllipsoidForm::Prolate; }
    }
}

SpheroidAxes Ellipsoid::determineSpheroidAxes()
{
    SpheroidAxes spheroid_axes;
    if (semi_axes[0] == semi_axes[1])
    {
        spheroid_axes.repeated = semi_axes[0];
        spheroid_axes.distinct = semi_axes[2];
    }
    else if (semi_axes[0] == semi_axes[2])
    {
        spheroid_axes.repeated = semi_axes[0];
        spheroid_axes.distinct = semi_axes[1];
    }
    else if (semi_axes[1] == semi_axes[2])
    {
        spheroid_axes.repeated = semi_axes[1];
        spheroid_axes.distinct = semi_axes[0];
    }
    else // Not a spheroid!
    {
        spheroid_axes.repeated = -1.0;
        spheroid_axes.distinct = -1.0;
    }
    return spheroid_axes;
}
