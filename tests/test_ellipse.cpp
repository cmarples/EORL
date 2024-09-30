#include <catch2/catch_test_macros.hpp>

#include "ellipse.hpp"
#include <Eigen/Core>
#include <array>

TEST_CASE("EllipseConstruction")
{
    Ellipse ellipse = Ellipse(2.0, 1.0);
    REQUIRE(ellipse.getA() == 2.0);
    REQUIRE(ellipse.getB() == 1.0);
    REQUIRE(ellipse.hasTransform() == false);

    ellipse.setCanonicalTransform();
    REQUIRE(ellipse.hasTransform() == false);

    ellipse.setPositionVector(1.0, 0.0);
    REQUIRE(ellipse.hasTransform() == true);

}

TEST_CASE("SettingAndGettingTransforms")
{
    Ellipse ellipse = Ellipse(2.0, 1.0);
    std::array<double, 2> inputPosition = {-1.0, 2.0};
    ellipse.setPositionVector(inputPosition);
    Eigen::Vector2d outputPosition = ellipse.getPositionVector();
    REQUIRE(outputPosition[0] == -1.0);
    REQUIRE(outputPosition[1] == 2.0);
}