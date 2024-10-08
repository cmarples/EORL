#include "ellipse.hpp"
#include <cmath>


Eigen::Vector2d Ellipse::computeClosestPerimeterPoint(const Eigen::Vector2d &query_point) const
{
    if (isCircle() == true)
    {
        return computeClosestPerimeterPoint(query_point);
    }
    else
    {

    }


    return Eigen::Vector2d(0,0);
}

Eigen::Vector2d Ellipse::computeClosestPerimeterPointCircle(const Eigen::Vector2d &query_point) const
{
    Eigen::Vector2d contact_point;
    Eigen::Vector2d centre_to_query = query_point - position;
    double centre_to_query_norm_squared = centre_to_query.squaredNorm();
    if (centre_to_query_norm_squared < 1.0e-14) // Point coincides with circle centre
    {
        contact_point = Eigen::Vector2d(semi_axes[0], 0.0) + position;
    }
    else
    {
        centre_to_query /= sqrt(centre_to_query_norm_squared);
        contact_point = semi_axes[0] * centre_to_query + position;
    }

    return contact_point;
}
