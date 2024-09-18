/**
 * @file Ellipsoid.hpp
 * @brief Defines the Ellipsoid class for 3D ellipsoids and provides related geometric functions.
 *
 * The Ellipsoid class represents an ellipsoid in 3D space, characterized by its center, 
 * semi-principal axes, and orientation. The class provides methods for various ellipsoid 
 * operations.
 *
 * The ellipsoid is defined by the equation: 
 * (x/a)^2 + (y/b)^2 + (z/c)^2 = 1
 * where a, b, and c are the lengths of the semi-principal axes.
 *
 * Usage:
 * @code
 * Ellipsoid ellipsoid(Vector3D(0, 0, 0), Vector3D(1, 2, 3), Matrix3x3::Identity());
 * double volume = ellipsoid.volume();
 * double surfaceArea = ellipsoid.surfaceArea();
 * @endcode
 */
#ifndef ELLIPSOID_HPP
#define ELLIPSOID_HPP

#include <array>

/**
 * @brief Represents a 3D ellipsoid with semi-principal axes, position and orientation.
 * This is the fundamental class of EORL. It provides methods to perform various geometric operations on the ellipsoid.
 */
class Ellipsoid
{
public:

    /********** Constructors **********/

    /**
     * @brief Default constructor.
     * Creates an ellipsoid with unit radius centered at the origin.
     */
    Ellipsoid();

    /**
     * @brief Parameterized constructor, with semi-principal axis lengths only.
     * @param a a axis of the ellipsoid.
     * @param b b axis of the ellipsoid.
     * @param c c axis of the ellipsoid.
     */
    Ellipsoid(const double& a, const double& b, const double& c);

    //Ellipsoid(const Vector3D& center, const Vector3D& radii, const Matrix3x3& orientation);

    /********** Getters **********/
    
    double getA() { return semi_axes[0]; }
    double getB() { return semi_axes[1]; }
    double getC() { return semi_axes[2]; }

    /********** Setters **********/

    void setA(double AxisA) { semi_axes[0] = AxisA; }
    void setB(double AxisB) { semi_axes[0] = AxisB; }
    void setC(double AxisC) { semi_axes[0] = AxisC; }

    /********** Output to Screen **********/

    /**
     * @brief Prints the axis lengths of the ellipsoid to the screen.
     */
    void printSemiAxes() const;

    

private:

    /**
     * @brief The semi-principal axes of the ellipsoid: {a, b, c}.
     * 
     * a, b, and c are the lengths of the ellipsoid's semi-principal axes along the x, y, and z axes, respectively.
     */
    std::array<double, 3> semi_axes;
};

















#endif // ELLIPSOID_HPP