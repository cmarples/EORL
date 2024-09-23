/**
 * @file ellipse.hpp
 * @brief Defines the Ellipsoid class for 2D ellipses and provides related geometric functions.
 *
 * The Ellipse class represents an ellipse in 2D space, characterized by its center, 
 * semi-principal axes, and orientation. The class provides methods for various ellipse 
 * operations.
 *
 * The ellipse is defined by the equation: 
 * (x/a)^2 + (y/b)^2 = 1
 * where a, and b are the lengths of the semi-principal axes.
 *
 * Usage:
 * @code
 * Ellipse ellipse_name = ellipse(Vector3D(0, 0, 0), Vector3D(1, 2, 3), Matrix3x3::Identity());
 * double volume = ellipsoid.volume();
 * double surfaceArea = ellipsoid.surfaceArea();
 * @endcode
 */
#ifndef ELLIPSE_HPP
#define ELLIPSE_HPP

#include <array>
#include <memory>

// Forward declare required types from Eigen.
namespace Eigen {
    template<typename Scalar, int Rows, int Cols, int Options, int MaxRows, int MaxCols>
    class Matrix;
    // Forward declare specific types based on Matrix template
    typedef Matrix<double, 2, 1, 0, 2, 1> Vector2d;
    typedef Matrix<double, 2, 2, 0, 2, 2> Matrix2d;
}

/**
 * @brief Represents a 2D ellipse with semi-principal axes, position and orientation.
 */
class Ellipse
{
public:

    /********** Constructors **********/

    /**
     * @brief Default constructor.
     * Creates a circle with unit radius centered at the origin.
     */
    Ellipse();

    /**
     * @brief Parameterized constructor, with semi-principal axis lengths only.
     * @param a a axis of the ellipse.
     * @param b b axis of the ellipse.
     */
    Ellipse(const double& a, const double& b);

    /********** Getters **********/
    
    double getA() { return semi_axes[0]; }
    double getB() { return semi_axes[1]; }
    std::array<double, 2> getPositionVector();

    /********** Setters **********/

    void setA(double AxisA) { semi_axes[0] = AxisA; }
    void setB(double AxisB) { semi_axes[0] = AxisB; }

    void setCanonicalTransform();
    void setPositionVector();
    void setPositionVector(std::array<double, 2>& position);
    void setRotationMatrix();
    void setRotationMatrix(std::array<std::array<double, 2>, 2>& rotation);

    /********** Output to Screen **********/

    /**
     * @brief Prints the axis lengths, position vector and rotation matrix of the ellipse to the screen.
     */
    void printEllipseTransform() const;

    /**
     * @brief Prints the axis lengths of the ellipse to the screen.
     */
    void printSemiAxes() const;

    void printPositionVector() const;

    void printRotationMatrix() const;

    /********** Queries **********/

    /**
     * @brief Returns true if both the position and orientation have been set.
     * 
     * In the context of EORL, a 'canonical ellipse' defined to have position vector (0, 0) 
     * and an identity rotation matrix.
     * 
     * The value of the boolean is false upon construction, with position and orientation pointers null.
     * Once both position and orientation pointers are not null, this boolean is set to true.
     */ 
    bool hasTransform() const;


private:

    /**
     * @brief The semi-principal axes of the ellipse: {a, b}.
     * 
     * a, b, and c are the lengths of the ellipse's semi-principal axes along the x, y, and z axes, respectively.
     */
    std::array<double, 2> semi_axes;

    /**
     * @brief The location of the ellipse centre, represented as a 2D position vector.
     */
    std::shared_ptr<Eigen::Vector2d> ptr_position;

    /**
     * @brief The orientation of the ellipse, represented as a 2x2 rotation matrix.
     */
    std::shared_ptr<Eigen::Matrix2d> ptr_orientation;

    
};

#endif // ELLIPSE_HPP