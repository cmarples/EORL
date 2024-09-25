#include "ellipse.hpp"
#include <Eigen/Core>
#include <cmath>


std::array<double, 2> Ellipse::computeClosestPerimeterPoint(const std::array<double, 2> &query_point) const
{
    if (isCircle() == true)
    {
        return computeClosestPerimeterPoint(query_point);
    }
    else
    {

    }


    return std::array<double, 2>();
}

std::array<double, 2> Ellipse::computeClosestPerimeterPointCircle(const std::array<double, 2> &query_point) const
{
    Eigen::Vector2d contact_point;
    Eigen::Vector2d query = Eigen::Map<const Eigen::Vector2d>(query_point.data());
    Eigen::Vector2d centre_to_query = query - *ptr_position;
    double centre_to_query_norm_squared = centre_to_query.squaredNorm();
    if (centre_to_query_norm_squared < 1.0e-14) // Point coincides with circle centre
    {
        contact_point = Eigen::Vector3d(semi_axes[0], 0.0) + *ptr_position;
    }
    else
    {
        centre_to_query /= sqrt(centre_to_query_norm_squared);
        contact_point = semi_axes[0] * centre_to_query + *ptr_position;
    }

    return { contact_point[0], contact_point[1] };
}
