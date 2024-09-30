#include <catch2/catch_test_macros.hpp>

#include "ellipsoid.hpp"

TEST_CASE("EllipsoidConstruction")
{
    Ellipsoid ellipsoid = Ellipsoid(3.0, 2.0, 1.0);
    REQUIRE(ellipsoid.getA() == 3.0);
    REQUIRE(ellipsoid.getB() == 2.0);
    REQUIRE(ellipsoid.getC() == 1.0);
    REQUIRE(ellipsoid.hasTransform() == false);

    ellipsoid.setCanonicalTransform();
    REQUIRE(ellipsoid.hasTransform() == false);

    ellipsoid.setPositionVector(0.0, 0.0, 1.0);
    REQUIRE(ellipsoid.hasTransform() == true);
}