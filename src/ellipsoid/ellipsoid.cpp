#include "ellipsoid.hpp"
#include <Eigen/Core>
#include <iostream>
#include <iomanip>

Ellipsoid::Ellipsoid()
{
    semi_axes = {1.0, 1.0, 1.0};
    position = Eigen::Vector3d(0.0, 0.0, 0.0);
    orientation = Eigen::Matrix3d::Identity();
    form = EllipsoidForm::Sphere;
}

Ellipsoid::Ellipsoid(double a_axis, double b_axis, double c_axis)
{
    semi_axes = {a_axis, b_axis, c_axis};
    position = Eigen::Vector3d(0.0, 0.0, 0.0);
    orientation = Eigen::Matrix3d::Identity();
    determineForm();
}

Eigen::Vector3d Ellipsoid::getPositionVector()
{
    return position;
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

void Ellipsoid::setSemiAxes(double a_axis, double b_axis, double c_axis)
{
    semi_axes = {a_axis, b_axis, c_axis};
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
    position = Eigen::Vector3d(0.0, 0.0, 0.0);
}

void Ellipsoid::setPositionVector(double x_coordinate, double y_coordinate, double z_coordinate)
{
    position = Eigen::Vector3d(x_coordinate, y_coordinate, z_coordinate);
}

void Ellipsoid::setPositionVector(std::array<double, 3>& input_position)
{
    position = Eigen::Vector3d(position[0], position[1], position[2]);
}

void Ellipsoid::setPositionVector(Eigen::Vector3d &input_position)
{
    position = input_position;
}

void Ellipsoid::setRotationMatrix()
{
    orientation = Eigen::Matrix3d::Identity();
}

void Ellipsoid::setRotationMatrix(std::array<std::array<double, 3>, 3>& input_rotation)
{
    orientation = Eigen::Map<Eigen::Matrix<double, 3, 3>>(input_rotation[0].data());
}

void Ellipsoid::setRotationMatrix(Eigen::Matrix3d &input_rotation)
{
    orientation = input_rotation;
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
    std::cout << position << "\n";
}

void Ellipsoid::printRotationMatrix() const
{
    std::cout << "Rotation matrix:\n";
    std::cout << orientation << "\n";
}

bool Ellipsoid::hasTransform() const
{
    return (position != Eigen::Vector3d(0.0, 0.0, 0.0) ||
         orientation != Eigen::Matrix3d::Identity());
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
    spheroid_axes.repeated = -1.0;
    spheroid_axes.distinct = -1.0;

    if (form != EllipsoidForm::Sphere)
    {
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
    }

    return spheroid_axes;
}
