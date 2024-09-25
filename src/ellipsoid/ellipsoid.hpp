/**
 * @file ellipsoid.hpp
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
#include <memory>

// Forward declare required types from Eigen.
namespace Eigen {
    template<typename Scalar, int Rows, int Cols, int Options, int MaxRows, int MaxCols>
    class Matrix;
    // Forward declare specific types based on Matrix template
    typedef Matrix<double, 3, 1, 0, 3, 1> Vector3d;
    typedef Matrix<double, 3, 3, 0, 3, 3> Matrix3d;
}

enum class EllipsoidForm
{
    Sphere,
    Oblate,
    Prolate,
    Triaxial
};

struct SpheroidAxes 
{
    double repeated;
    double distinct;
};

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

    std::array<double, 3> getPositionVector();

    /********** Setters **********/

    void setA(double a_axis);
    void setB(double b_axis);
    void setC(double c_axis);
    void setSemiAxes(std::array<double, 3> axes);

    void setCanonicalTransform();
    void setPositionVector();
    void setPositionVector(std::array<double, 3>& position);
    void setRotationMatrix();
    void setRotationMatrix(std::array<std::array<double, 3>, 3>& rotation);

    /********** Output to Screen **********/

    /**
     * @brief Prints the axis lengths, position vector and rotation matrix of the ellipsoid to the screen.
     */
    void printEllipsoidTransform() const;

    /**
     * @brief Prints the axis lengths of the ellipsoid to the screen.
     */
    void printSemiAxes() const;

    void printPositionVector() const;

    void printRotationMatrix() const;

    /********** Queries **********/

    /**
     * @brief Returns true if both the position and orientation have been set.
     * 
     * In the context of EORL, a 'canonical ellipsoid' defined to have position vector (0, 0, 0) 
     * and an identity rotation matrix.
     * 
     * The value of the boolean is true upon construction, with position and orientation pointers null.
     * Once both position and orientation pointers are not null, this boolean is set to false.
     */ 
    bool hasTransform() const;

    bool isSphere() const;
    bool isSpheroid() const;
    bool isOblate();
    bool isProlate();
    bool isTriaxial() const;

    /********** Internal Handling **********/

    void determineForm();
    SpheroidAxes determineSpheroidAxes();

    /********** Distances and Intersections **********/

    std::array<double, 3> computeClosestSurfacePoint(const std::array<double, 3>& query_point) const;
    std::array<double, 3> computeClosestSurfacePointSphere(const std::array<double, 3>& query_point) const;


private:

    /**
     * @brief The semi-principal axes of the ellipsoid: {a, b, c}.
     * 
     * a, b, and c are the lengths of the ellipsoid's semi-principal axes along the x, y, and z axes, respectively.
     */
    std::array<double, 3> semi_axes;

    /**
     * @brief The location of the ellipsoid centre, represented as a 3D position vector.
     */
    std::shared_ptr<Eigen::Vector3d> ptr_position;

    /**
     * @brief The orientation of the ellipsoid, represented as a 3x3 rotation matrix.
     */
    std::shared_ptr<Eigen::Matrix3d> ptr_orientation;

    EllipsoidForm form;
};

















#endif // ELLIPSOID_HPP