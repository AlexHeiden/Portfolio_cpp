#define USE_MATH_DEFINES

#include <cmath>
#include <boost/test/unit_test.hpp>
#include "circle.hpp"
#include "base-types.hpp"

BOOST_AUTO_TEST_SUITE(tests_for_circles)

const double epsilon = 0.0001;
const double radius = 5.0;
const double area = M_PI * radius * radius;
const stepanov::point_t center = { 4.0, 5.0 };

BOOST_AUTO_TEST_CASE(circle_parameters_immutability_after_move_on_axis_test)
{
  stepanov::Circle circle(center, radius);
  const double dx = 5.0;
  const double dy = 6.0;
  circle.move(dx, dy);
  BOOST_CHECK_CLOSE(circle.getRadius(), radius, epsilon);
  BOOST_CHECK_CLOSE(circle.getArea(), area, epsilon);
  BOOST_CHECK_CLOSE(circle.getCenter().x, center.x + dx, epsilon);
  BOOST_CHECK_CLOSE(circle.getCenter().y, center.y + dy, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().width, 2 * radius, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().height, 2 * radius, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, center.x + dx, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, center.y + dy, epsilon);
}

BOOST_AUTO_TEST_CASE(circle_parameters_immutability_after_moving_in_point_test)
{
  stepanov::Circle circle(center, radius);
  const stepanov::point_t newCenter = { 3.4, 5.6 };
  circle.move(newCenter);
  BOOST_CHECK_CLOSE(circle.getRadius(), radius, epsilon);
  BOOST_CHECK_CLOSE(circle.getArea(), area, epsilon);
  BOOST_CHECK_CLOSE(circle.getCenter().x, newCenter.x, epsilon);
  BOOST_CHECK_CLOSE(circle.getCenter().y, newCenter.y, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().width, 2 * radius, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().height, 2 * radius, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, newCenter.x, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, newCenter.y, epsilon);
}

BOOST_AUTO_TEST_CASE(circle_afterscale_area_test)
{
  stepanov::Circle circle(center, radius);
  const double coefficient = 4.0;
  circle.scale(coefficient);
  BOOST_CHECK_CLOSE(circle.getArea(), area * coefficient * coefficient, epsilon);
  BOOST_CHECK_CLOSE(circle.getRadius(), radius * coefficient, epsilon);
  BOOST_CHECK_CLOSE(circle.getCenter().x, center.x, epsilon);
  BOOST_CHECK_CLOSE(circle.getCenter().y, center.y, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().height, circle.getRadius() * 2, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().width, circle.getRadius() * 2, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, center.x, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, center.y, epsilon);
}

BOOST_AUTO_TEST_CASE(circle_valid_arguments_test)
{
  stepanov::Circle circle(center, radius);
  BOOST_CHECK_CLOSE(circle.getRadius(), radius, epsilon);
  BOOST_CHECK_CLOSE(circle.getArea(), area, epsilon);
  BOOST_CHECK_CLOSE(circle.getCenter().x, center.x, epsilon);
  BOOST_CHECK_CLOSE(circle.getCenter().y, center.y, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().width, 2 * radius, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().height, 2 * radius, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, center.x, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, center.y, epsilon);
}

BOOST_AUTO_TEST_CASE(circle_rotate_test)
{
  stepanov::Circle circle(center, radius);
  circle.rotate(45);
  BOOST_CHECK_CLOSE(circle.getRadius(), radius, epsilon);
  BOOST_CHECK_CLOSE(circle.getArea(), area, epsilon);
  BOOST_CHECK_CLOSE(circle.getCenter().x, center.x, epsilon);
  BOOST_CHECK_CLOSE(circle.getCenter().y, center.y, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().width, 2 * radius, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().height, 2 * radius, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, center.x, epsilon);
  BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, center.y, epsilon);
}

BOOST_AUTO_TEST_CASE(circle_invalid_radius_test)
{
  BOOST_CHECK_THROW(stepanov::Circle(center, -radius), std::invalid_argument);
  const double zeroRadius = 0.0;
  BOOST_CHECK_THROW(stepanov::Circle(center, zeroRadius), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(rectangle_invalid_scale_coefficient_test)
{
  stepanov::Circle circle(center, radius);
  double coefficient = -5.0;
  BOOST_CHECK_THROW(circle.scale(coefficient), std::invalid_argument);
  coefficient = 0.0;
  BOOST_CHECK_THROW(circle.scale(coefficient), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
