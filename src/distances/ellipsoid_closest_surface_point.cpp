#include "ellipsoid.hpp"
#include <Eigen/Core>
#include <cmath>

std::array<double, 3> Ellipsoid::computeClosestSurfacePoint(const std::array<double, 3> &query_point) const
{
    

    if (form == EllipsoidForm::Sphere)
    {
        return computeClosestSurfacePointSphere(query_point);
    }


    return std::array<double, 3>();
}

std::array<double, 3> Ellipsoid::computeClosestSurfacePointSphere(const std::array<double, 3> &query_point) const
{
    Eigen::Vector3d contact_point;
    Eigen::Vector3d query = Eigen::Map<const Eigen::Vector3d>(query_point.data());
    Eigen::Vector3d centre_to_query = query - *ptr_position;
    double centre_to_query_norm_squared = centre_to_query.squaredNorm();
    if (centre_to_query_norm_squared < 1.0e-14) // Point coincides with sphere centre
    {
        contact_point = Eigen::Vector3d(semi_axes[0], 0.0, 0.0) + *ptr_position;
    }
    else
    {
        centre_to_query /= sqrt(centre_to_query_norm_squared);
        contact_point = semi_axes[0] * centre_to_query + *ptr_position;
    }

    return { contact_point[0], contact_point[1], contact_point[2] };
}
