#include "ellipsoid.hpp"
#include <Eigen/Core>
#include <cmath>

Eigen::Vector3d Ellipsoid::computeClosestSurfacePoint(const Eigen::Vector3d& query_point) const
{
    

    if (form == EllipsoidForm::Sphere)
    {
        return computeClosestSurfacePointSphere(query_point);
    }


    return Eigen::Vector3d(0.0, 0.0, 0.0);
}

Eigen::Vector3d Ellipsoid::computeClosestSurfacePointSphere(const Eigen::Vector3d& query_point) const
{
    Eigen::Vector3d contact_point;
    Eigen::Vector3d centre_to_query = query_point - position;
    double centre_to_query_norm_squared = centre_to_query.squaredNorm();
    if (centre_to_query_norm_squared < 1.0e-14) // Point coincides with sphere centre
    {
        contact_point = Eigen::Vector3d(semi_axes[0], 0.0, 0.0) + position;
    }
    else
    {
        centre_to_query /= sqrt(centre_to_query_norm_squared);
        contact_point = semi_axes[0] * centre_to_query + position;
    }

    return contact_point;
}
